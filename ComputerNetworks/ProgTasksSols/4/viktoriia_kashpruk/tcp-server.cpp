// Viktoriia Kashpruk 337014
#include <arpa/inet.h>
#include <errno.h>
#include <poll.h>
#include <sys/time.h>
#include <unistd.h>

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <vector>
#include <numeric>

namespace fs = std::filesystem;

void ERROR(const char *str)
{
    std::cerr << str << ": " << strerror(errno) << std::endl;
    exit(EXIT_FAILURE);
}

int poll_wrapper(int fd, int *max_waiting_time)
{
    timeval clock_before{}, clock_after{}, time_elapsed{};
    pollfd ps{};

    gettimeofday(&clock_before, nullptr);
    ps.fd = fd;
    ps.events = POLLIN;
    ps.revents = 0;

    int ready = poll(&ps, 1, *max_waiting_time);
    if (ready < 0 || (ready > 0 && !(ps.revents & POLLIN)))
        ERROR("poll error");
    if (ready == 0)
    {
        *max_waiting_time = 0;
        return 0;
    }

    gettimeofday(&clock_after, nullptr);
    timersub(&clock_after, &clock_before, &time_elapsed);
    *max_waiting_time -= static_cast<int>(time_elapsed.tv_sec * 1000 + time_elapsed.tv_usec / 1000);
    if (*max_waiting_time < 0)
        *max_waiting_time = 0;

    return 1;
}

std::string recv_http_request(int fd, int timeout_ms)
{
    std::string request;
    char buf[1024];
    int max_waiting_time = timeout_ms;

    while (true)
    {
        int ret = poll_wrapper(fd, &max_waiting_time);
        if (ret == 0)
            break;

        ssize_t bytes = recv(fd, buf, sizeof(buf), 0);
        if (bytes < 0)
            ERROR("recv error");

        if (bytes == 0)
            break;

        request.append(buf, bytes);

        if (request.find("\r\n\r\n") != std::string::npos)
            break;
    }

    return request;
}

struct HttpRequest
{
    std::string method;
    std::string path;
    std::string version;
    std::string host;
    std::string connection;
};

HttpRequest parseRequest(const std::string &request)
{
    HttpRequest req;

    size_t host_pos = request.find("Host:");
    if (host_pos == std::string::npos)
    {
        host_pos = request.find("host:");
    }

    if (host_pos != std::string::npos)
    {
        size_t line_start = host_pos + 5;
        size_t line_end = request.find('\n', line_start);
        if (line_end != std::string::npos)
        {
            req.host = request.substr(line_start, line_end - line_start);
            size_t start = req.host.find_first_not_of(" \t\r");
            size_t end = req.host.find_last_not_of(" \t\r");
            if (start != std::string::npos && end != std::string::npos)
            {
                req.host = req.host.substr(start, end - start + 1);
            }

            size_t colon_pos = req.host.find(':');
            if (colon_pos != std::string::npos)
            {
                req.host = req.host.substr(0, colon_pos);
            }
        }
    }

    size_t conn_pos = request.find("Connection:");
    if (conn_pos == std::string::npos)
    {
        conn_pos = request.find("connection:");
    }

    if (conn_pos != std::string::npos)
    {
        size_t line_start = conn_pos + 11;
        size_t line_end = request.find('\n', line_start);
        if (line_end != std::string::npos)
        {
            req.connection = request.substr(line_start, line_end - line_start);
            size_t start = req.connection.find_first_not_of(" \t\r");
            size_t end = req.connection.find_last_not_of(" \t\r");
            if (start != std::string::npos && end != std::string::npos)
            {
                req.connection = req.connection.substr(start, end - start + 1);
            }
        }
    }

    size_t first_line_end = request.find('\n');
    if (first_line_end != std::string::npos)
    {
        std::string first_line = request.substr(0, first_line_end);
        if (!first_line.empty() && first_line.back() == '\r')
        {
            first_line.pop_back();
        }

        std::istringstream iss(first_line);
        iss >> req.method >> req.path >> req.version;

        if (req.path.rfind("http://", 0) == 0 || req.path.rfind("https://", 0) == 0)
        {

            size_t path_start = req.path.find('/', req.path.find("://") + 3);
            if (path_start != std::string::npos)
                req.path = req.path.substr(path_start);
            else
                req.path = "/";
        }
    }

    return req;
}

std::string getContentType(const std::string &path)
{
    size_t dot_pos = path.find_last_of('.');
    if (dot_pos == std::string::npos)
        return "application/octet-stream";

    std::string ext = path.substr(dot_pos + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    if (ext == "txt")
        return "text/plain";
    if (ext == "html" || ext == "htm")
        return "text/html";
    if (ext == "css")
        return "text/css";
    if (ext == "jpg" || ext == "jpeg")
        return "image/jpeg";
    if (ext == "png")
        return "image/png";
    if (ext == "pdf")
        return "application/pdf";

    return "application/octet-stream";
}

void sendAll(int fd, const char *data, size_t length)
{
    size_t total = 0;
    while (total < length)
    {
        ssize_t sent = send(fd, data + total, length - total, 0);
        if (sent <= 0)
            ERROR("send error");
        total += sent;
    }
}

void handleGetRequest(int client_fd, const HttpRequest &req, const std::string &base_catalog)
{
    bool keep_alive = (req.version == "HTTP/1.1");
    if (!req.connection.empty())
    {
        std::string lower_conn = req.connection;
        std::transform(lower_conn.begin(), lower_conn.end(), lower_conn.begin(), ::tolower);
        keep_alive = (lower_conn == "keep-alive");
    }

    if (req.path.find("..") != std::string::npos)
    {
        std::string forbidden = "<html><body><h1>403 Forbidden</h1></body></html>";
        std::ostringstream response_headers;
        response_headers << "HTTP/1.1 403 Forbidden\r\n"
                         << "Content-Type: text/html\r\n"
                         << "Content-Length: " << forbidden.size() << "\r\n"
                         << "Connection: close\r\n"
                         << "\r\n";

        std::string headers_str = response_headers.str();
        sendAll(client_fd, headers_str.c_str(), headers_str.size());
        sendAll(client_fd, forbidden.data(), forbidden.size());
        close(client_fd);
        return;
    }
    // std::cout << "HOST:: " << req.host << std::endl;

    fs::path relative_path = fs::path(req.path).relative_path();

    if (!relative_path.empty() && relative_path.begin()->string() == req.host)
    {
        relative_path = std::accumulate(
            std::next(relative_path.begin()), relative_path.end(), fs::path{},
            [](const fs::path &a, const fs::path &b)
            {
                return a / b;
            });
    }

    fs::path full_path = fs::path(base_catalog) / req.host / relative_path;
    int status_code = 200;
    std::cout << full_path << std::endl;
    std::vector<char> body;
    std::string status_text = "OK";
    std::string content_type = "text/html";
    if (fs::is_directory(full_path))
    {
        // std::cout << "Weszlo " << full_path << std::endl;
        fs::path index_path = full_path / "index.html";

        std::string new_location = req.path;
        if (new_location.back() != '/')
            new_location += "/";
        new_location += "index.html";

        std::ostringstream response_headers;
        response_headers << "HTTP/1.1 301 Moved Permanently\r\n"
                         << "Location: " << new_location << "\r\n"
                         << "Content-Length: 0\r\n"
                         << "Connection: " << (keep_alive ? "keep-alive" : "close") << "\r\n"
                         << "\r\n";
        std::string headers_str = response_headers.str();
        sendAll(client_fd, headers_str.c_str(), headers_str.size());
        if (!keep_alive)
            close(client_fd);
        return;
    }

    if (fs::exists(full_path) && fs::is_regular_file(full_path))
    {
        std::ifstream file(full_path, std::ios::binary);
        body = std::vector<char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        content_type = getContentType(full_path.string());
    }
    else
    {
        status_code = 404;
        status_text = "Not Found";
        std::string not_found = "<html><body><h1>404 Not Found</h1></body></html>";
        body = std::vector<char>(not_found.begin(), not_found.end());
        content_type = "text/html";
    }

    std::ostringstream response_headers;
    response_headers << "HTTP/1.1 " << status_code << " " << status_text << "\r\n"
                     << "Content-Type: " << content_type << "\r\n"
                     << "Content-Length: " << body.size() << "\r\n"
                     << "Connection: " << (keep_alive ? "keep-alive" : "close") << "\r\n"
                     << "\r\n";

    std::string headers_str = response_headers.str();
    sendAll(client_fd, headers_str.c_str(), headers_str.size());
    if (!body.empty())
        sendAll(client_fd, body.data(), body.size());

    if (!keep_alive)
        close(client_fd);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <port> <base_catalog>" << std::endl;
        return EXIT_FAILURE;
    }

    int port = std::stoi(argv[1]);
    std::string base_catalog = argv[2];

    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
        ERROR("socket error");

    int optval = 1;
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock_fd, reinterpret_cast<sockaddr *>(&server_address), sizeof(server_address)) < 0)
        ERROR("bind error");

    if (listen(sock_fd, 64) < 0)
        ERROR("listen error");

    std::cout << "Server running on port " << port << ", serving from base catalog: " << base_catalog << std::endl;

    while (true)
    {
        int client_fd = accept(sock_fd, nullptr, nullptr);
        if (client_fd < 0)
            ERROR("accept error");

        while (true)
        {
            std::string request = recv_http_request(client_fd, 250);
            if (request.empty())
            {
                close(client_fd);
                break;
            }

            HttpRequest req = parseRequest(request);

            if (req.method == "GET")
            {
                handleGetRequest(client_fd, req, base_catalog);
                if (req.connection.empty() || req.connection == "close")
                    break;
            }
            else
            {

                const char *resp = "HTTP/1.1 501 Not Implemented\r\nContent-Length: 0\r\nConnection: close\r\n\r\n";
                sendAll(client_fd, resp, strlen(resp));
                close(client_fd);
                break;
            }
        }
    }

    close(sock_fd);
    return 0;
}