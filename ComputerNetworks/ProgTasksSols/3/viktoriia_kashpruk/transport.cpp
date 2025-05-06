// Viktoriia Kashpruk 337014

#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>
#include <unistd.h>
#include <errno.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <array>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <chrono>

using namespace std;
constexpr int SEG_SIZE = 1000;
constexpr int WINDOW_SIZE = 200;
constexpr int RETRANSMIT_DELAY_MS = 0;

void error_exit(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

class Window {
    using Clock = chrono::steady_clock;

    int total_size;
    int segments;
    int received_count = 0;

    int lar = -1; // last acknowledgement recieved
    int lss = -1; // largest (by id) segment sent
    vector<Clock::time_point> last_sent;

    vector<array<char, SEG_SIZE>>  buf;
    vector<bool> recieved_in_window;

public:
    explicit Window(int total_size)
        : total_size(total_size),
          segments((total_size + SEG_SIZE - 1) / SEG_SIZE),
          buf(WINDOW_SIZE),
          recieved_in_window(WINDOW_SIZE,false)
    {
        last_sent.resize(WINDOW_SIZE, Clock::now() - chrono::milliseconds(RETRANSMIT_DELAY_MS+1));
    }

    bool is_complete() const {
        return received_count == segments;
    }

    int get_total_segments() const {
        return segments;
    }

    int get_lar() const {
        return lar;
    }

    bool can_send_next() const {
        return (lss < segments - 1) && (lss - lar < WINDOW_SIZE);
    }

    int next_segment_to_send() const {
        return lss + 1;
    }

    bool should_retransmit(int i) const {
        if (recieved_in_window[i % WINDOW_SIZE]) return false;
        auto now = Clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(now - last_sent[i % WINDOW_SIZE]).count();
        return elapsed >= RETRANSMIT_DELAY_MS;
    }

    void mark_sent(int i) {
        last_sent[i % WINDOW_SIZE] = Clock::now();
        lss = max(lss, i);
    }

    bool already_received(int start) const {
        int id = start / SEG_SIZE;
        return recieved_in_window[id % WINDOW_SIZE];
    }

    void store_segment(int start, const char* data, int len) {
        int id = start / SEG_SIZE;
        int idx = id % WINDOW_SIZE;
        if (recieved_in_window[idx]) return;
        memcpy(buf[idx].data(), data, len);
        recieved_in_window[idx] = true;
        received_count++;
        while (lar+1 < segments && recieved_in_window[(lar+1) % WINDOW_SIZE]) {
            lar++;

        }
    }

    void clear(int id) {
        recieved_in_window[id % WINDOW_SIZE] = false;
    }

    const char* segment_data(int id) const {
        return buf[id % WINDOW_SIZE].data();
    }

    int segment_length(int id) const {
        return min(SEG_SIZE, total_size - id*SEG_SIZE);
    }

    int get_start(int id) const {
        return id * SEG_SIZE;
    }

    int get_length(int id) const {
        return min(SEG_SIZE, total_size - get_start(id));
    }

    int get_total_size() const {
        return total_size;
    }

    vector<int> segments_in_flight() const {
        vector<int> inflight;
        for (int i = lar + 1; i <= lss; ++i) {
            if (!recieved_in_window[i % WINDOW_SIZE]) inflight.push_back(i);
        }
        return inflight;
    }
};

class UDPSender {
    int sockfd;
    sockaddr_in server;

public:
    UDPSender(int sockfd, const string& ip, int port) : sockfd(sockfd) {
        server.sin_family = AF_INET;
        server.sin_port = htons(port);
        inet_pton(AF_INET, ip.c_str(), &server.sin_addr);
    }

    void send_get(int start, int len) {
        char msg[64];
        snprintf(msg, sizeof(msg), "GET %d %d\n", start, len);
        sendto(sockfd, msg, strlen(msg), 0, (sockaddr*)&server, sizeof(server));
    }

    const sockaddr_in& get_server_addr() const {
        return server;
    }
};

class UDPReceiver {
    int sockfd;
    const sockaddr_in& server_addr;

public:
    UDPReceiver(int sockfd, const sockaddr_in& addr) : sockfd(sockfd), server_addr(addr) {}

    void receive_all(Window& window) {
        while (true) {
            bool res = receive(window);

            if (res <= 0) {
                break;
            }
        }
    }

    int receive(Window& window) {
        char buf[1500];
        sockaddr_in src {};
        socklen_t slen = sizeof(src);

        ssize_t len = recvfrom(sockfd, buf, sizeof(buf), 0, (sockaddr*)&src, &slen);
        if (len < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                return 0;
            }
            perror("recvfrom");
            return -1;
        }

        char ipstr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(src.sin_addr), ipstr, sizeof(ipstr));
        if (src.sin_addr.s_addr != server_addr.sin_addr.s_addr) return 1;
        if (src.sin_port != server_addr.sin_port) return 1;

        string packet(buf, len);
        size_t newline = packet.find('\n');
        if (newline == string::npos) return 1;

        string header = packet.substr(0, newline);
        istringstream iss(header);
        string tag;
        int start = 0, length = 0;
        iss >> tag >> start >> length;
        if (tag != "DATA" || iss.fail()) return 1;

        if (window.already_received(start) || start / SEG_SIZE <= window.get_lar()) {
            return 1;
        }
        window.store_segment(start, buf + newline + 1, length);
        return 1;
    }
};

class FileWriter {
    string filename;
    int fd;
public:
    FileWriter(const string& fname) : filename(fname) {
        fd = open(filename.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) error_exit("open");
    }

    ~FileWriter() {
        close(fd);
    }

    void write_chunk(const char* data, int size) {
        ssize_t written = ::write(fd, data, size);
        if (written != size) error_exit("write");
    }
};

class TransportClient {
    string ip;
    int port;
    string filename;
    int total_size;

public:
    TransportClient(const string& ip, int port, const string& filename, int total_size)
        : ip(ip), port(port), filename(filename), total_size(total_size) {}

    void run() {
        int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd < 0) error_exit("socket");

        fcntl(sockfd, F_SETFL, O_NONBLOCK);

        Window window(total_size);
        UDPSender sender(sockfd, ip, port);
        UDPReceiver receiver(sockfd, sender.get_server_addr());
        FileWriter writer(filename);

        int last_written_id = -1;

        while (!window.is_complete()) {
            while (window.can_send_next()) {
                int id = window.next_segment_to_send();
                sender.send_get(window.get_start(id), window.get_length(id));
                window.mark_sent(id);
            }

            pollfd pfd = {sockfd, POLLIN, 0};
            int ready = poll(&pfd, 1, 10);
            if (ready > 0 && (pfd.revents & POLLIN)) {
                receiver.receive_all(window);
            }

            while (last_written_id < window.get_lar()) {
                const int next = last_written_id + 1;
                writer.write_chunk(window.segment_data(next), window.segment_length(next));
                window.clear(next);
                last_written_id = next;
            }

            for (const int id : window.segments_in_flight()) {
                if (window.should_retransmit(id)) {
                    sender.send_get(window.get_start(id), window.get_length(id));
                    window.mark_sent(id);
                }
            }
        }

        close(sockfd);
    }
};

int main(int argc, char* argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <ip> <port> <filename> <size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    string ip = argv[1];
    int port = atoi(argv[2]);
    string filename = argv[3];
    int size = atoi(argv[4]);

    if (port <= 0 || size <= 0 || size > 10'000'000) {
        fprintf(stderr, "Invalid arguments\n");
        return EXIT_FAILURE;
    }

    TransportClient client(ip, port, filename, size);
    client.run();

    return 0;
}
