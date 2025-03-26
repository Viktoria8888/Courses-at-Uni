#include "icmp_send.h"
#include "icmp_utils.h"
#include <chrono>
#include <iostream>
#include <poll.h>
#include <set>
#include <string> 

void get_ip(struct sockaddr_in sender, char *sender_ip_str, size_t size) {
  inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, size);
}

void print_ip(int n, std::string ip, double avg_time) {
  std::cout << n << ". " << ip << " " << avg_time << " ms" << std::endl;
}

void traceroute(int sock_fd, const char *recipientIP) {
  bool destination_reached = false;
  int ttl = 0;
  pid_t pid = getpid();
  u_int16_t id = pid & 0xFFFF;

  while (!destination_reached) {
    ttl++;
    double avg_time = 0.0;
    std::set<std::string> ips;

    auto start_time = std::chrono::steady_clock::now();
    for (int i = 0; i < N_PACKETS; i++) {
      send_icmp_packet(sock_fd, ttl, ttl, recipientIP);
    }

    int packets_received = 0;

    while (packets_received < N_PACKETS && !destination_reached) {
      auto current_time = std::chrono::steady_clock::now();
      auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
          current_time - start_time);

      int remaining_timeout_ms = TIMEOUT_MSECS - elapsed_time.count();
      if (remaining_timeout_ms <= 0) {
        break;
      }

      struct pollfd ps;
      ps.fd = sock_fd;
      ps.events = POLLIN;
      ps.revents = 0;

      int ready = poll(&ps, 1, remaining_timeout_ms);
      if (ready == 0){
        std::cout<<ttl<<". "<<"*"<<std::endl;
      }
      else if (ready > 0) {
        if (ps.revents == POLLIN) {
          while (1) {
            struct sockaddr_in sender;
            socklen_t sender_len = sizeof(sender);
            u_int8_t buffer[IP_MAXPACKET];
            ssize_t packet_len =
                recvfrom(sock_fd, buffer, IP_MAXPACKET, 0,
                         (struct sockaddr *)&sender, &sender_len);

            if (packet_len < 0) {
              if (errno == EAGAIN || errno == EWOULDBLOCK) {
                break;
              } else {
                ERROR("recvfrom error");
              }
            } else {
              struct ip *new_ip_header = (struct ip *)buffer;
              ssize_t new_ip_header_len = 4 * (ssize_t)(new_ip_header->ip_hl);
              struct icmp *new_icmp_header =
                  (struct icmp *)(buffer + new_ip_header_len);

              if (new_icmp_header->icmp_type == ICMP_ECHOREPLY) {
                destination_reached = true;
                char sender_ip_str[20];
                get_ip(sender, sender_ip_str, sizeof(sender_ip_str));
                ips.insert(sender_ip_str);
                break;

              } else if (new_icmp_header->icmp_type == ICMP_TIME_EXCEEDED) {
                struct ip *old_ip_header =
                    (struct ip *)((char *)new_icmp_header + 8);
                ssize_t old_ip_header_len = 4 * (ssize_t)(old_ip_header->ip_hl);
                struct icmp *old_icmp_header =
                    (struct icmp *)((char *)old_ip_header + old_ip_header_len);

                int seq = old_icmp_header->icmp_hun.ih_idseq.icd_seq;
                int packetId = htons(old_icmp_header->icmp_hun.ih_idseq.icd_id);
                char sender_ip_str[20];
                get_ip(sender, sender_ip_str, sizeof(sender_ip_str));

                if (seq == ttl && id == packetId) {
                  packets_received++;
                  auto packet_time = std::chrono::steady_clock::now();
                  auto rtt =
                      std::chrono::duration_cast<std::chrono::milliseconds>(
                          packet_time - start_time)
                          .count();
                  avg_time += static_cast<double>(rtt);
                  ips.insert(sender_ip_str);
                  // std::cout<<"ips size: "<<ips.size()<<std::endl;
                  if (packets_received == N_PACKETS)
                    break;
                }
              }
            }
          }
        }
      }
    }

    if (!ips.empty()) {
      std::string first_ip = *ips.begin();
      print_ip(ttl, first_ip, avg_time / N_PACKETS);
    }

    // if (packets_received == N_PACKETS) {
    //     std::cout << "All " << N_PACKETS << " packets received for TTL=" <<
    //     ttl
    //               << ". Proceeding to the next TTL.\n";
    // }
  }
}

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    ERROR("wrong number of arguments");
  }
  int sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  if (sock_fd < 0) {
    std::cerr << "socket error: " << strerror(errno) << std::endl;
    ERROR("socket error");
  }

  const char *recipientIP = argv[1];
  traceroute(sock_fd, recipientIP);
  close(sock_fd);
  return 0;
}