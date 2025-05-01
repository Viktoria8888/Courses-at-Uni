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
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <chrono>

using namespace std;
constexpr int SEG_SIZE = 1000;
constexpr int WINDOW_SIZE = 5;
constexpr int RETRANSMIT_DELAY_MS = 1000;

void error_exit(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

class Window {
    using Clock = chrono::steady_clock;

    vector<char> data;
    vector<bool> received;
    int total_size;
    int segments;
    int received_count = 0;

    int lar = -1;
    int lfs = -1;

    unordered_map<int, int> retries;
    unordered_map<int, Clock::time_point> last_sent;

public:
    Window(int total_size)
        : total_size(total_size),
          data(total_size),
          received((total_size + SEG_SIZE - 1) / SEG_SIZE, false),
          segments((total_size + SEG_SIZE - 1) / SEG_SIZE) {
        for (int i = 0; i < segments; ++i) {
            retries[i] = 5;
            last_sent[i] = Clock::now() - chrono::milliseconds(RETRANSMIT_DELAY_MS + 1);
        }
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

    int get_lfs() const {
        return lfs;
    }

    bool can_send_next() const {
        return (lfs < segments - 1) && (lfs - lar < WINDOW_SIZE);
    }

    int next_segment_to_send() {
        return lfs + 1;
    }

    bool should_retransmit(int i) const {
        if (received[i] || retries.at(i) <= 0) return false;
        auto now = Clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(now - last_sent.at(i)).count();
        return elapsed >= RETRANSMIT_DELAY_MS;
    }

    void mark_sent(int i) {
        last_sent[i] = Clock::now();
        retries[i]--;
        lfs = max(lfs, i);
    }

    bool already_received(int start) const {
        int id = start / SEG_SIZE;
        return received[id];
    }

    void store_segment(int start, const char* buf, int len) {
        int id = start / SEG_SIZE;
        if (!received[id]) {
            memcpy(&data[start], buf, len);
            received[id] = true;
            received_count++;


            while (lar + 1 < segments && received[lar + 1]) {
                lar++;
            }
        }
    }

    int get_start(int id) const {
        return id * SEG_SIZE;
    }

    int get_length(int id) const {
        return min(SEG_SIZE, total_size - get_start(id));
    }

    const char* get_data() const {
        return data.data();
    }

    int get_total_size() const {
        return total_size;
    }

    vector<int> segments_in_flight() const {
        vector<int> inflight;
        for (int i = lar + 1; i <= lfs; ++i) {
            if (!received[i]) inflight.push_back(i);
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

    bool receive(Window& tracker) {
        char buf[1500];
        sockaddr_in src {};
        socklen_t slen = sizeof(src);

        ssize_t len = recvfrom(sockfd, buf, sizeof(buf), 0, (sockaddr*)&src, &slen);
        if (len < 0) return false;

        char ipstr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(src.sin_addr), ipstr, sizeof(ipstr));
        if (ntohs(src.sin_port) != ntohs(server_addr.sin_port)) return false;

        string packet(buf, len);
        size_t newline = packet.find('\n');
        if (newline == string::npos) return false;

        string header = packet.substr(0, newline);
        istringstream iss(header);
        string tag;
        int start = 0, length = 0;
        iss >> tag >> start >> length;
        if (tag != "DATA" || iss.fail()) return false;

        if (tracker.already_received(start)) return true;

        tracker.store_segment(start, buf + newline + 1, length);
        return true;
    }
};

class FileWriter {
    string filename;

public:
    FileWriter(const string& fname) : filename(fname) {}

    void write(const char* data, int size) {
        int fd = open(filename.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) error_exit("open");

        ssize_t written = ::write(fd, data, size);
        if (written != size) error_exit("write");

        close(fd);
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

        while (!window.is_complete()) {
            // Send new GETs within the window
            while (window.can_send_next()) {
                int id = window.next_segment_to_send();
                sender.send_get(window.get_start(id), window.get_length(id));
                window.mark_sent(id);
            }

            // Poll for data
            pollfd pfd = {sockfd, POLLIN, 0};
            int ready = poll(&pfd, 1, 300);

            if (ready > 0 && (pfd.revents & POLLIN)) {
                receiver.receive(window);
            }


            for (int id : window.segments_in_flight()) {
                if (window.should_retransmit(id)) {
                    sender.send_get(window.get_start(id), window.get_length(id));
                    window.mark_sent(id);
                }
            }
        }

        writer.write(window.get_data(), window.get_total_size());
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