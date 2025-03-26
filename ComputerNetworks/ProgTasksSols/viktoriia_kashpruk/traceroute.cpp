// Viktoriia Kashpruk 337014
#include "icmp_send.h"
#include "icmp_utils.h"
#include <chrono>
#include <poll.h>
#include <utility>

std::pair<int, bool> poll_socket(int sock_fd, int remaining_timeout_ms) {
  struct pollfd ps;
  ps.fd = sock_fd;
  ps.events = POLLIN;
  ps.revents = 0;

  return {poll(&ps, 1, remaining_timeout_ms), ps.revents == POLLIN};
}
// To była jedyna zmiana :
// void validate_packet(int seq, int ttl, u_int16_t packetId, u_int16_t id,
//                      int &packets_received, int &dest_packets, bool dest,
//                      double &avg_time,
//                      std::chrono::steady_clock::time_point start_time) {
//   if (seq == ttl && id == packetId) {
//     packets_received++;
//     auto rtt = std::chrono::duration_cast<std::chrono::milliseconds>(
//                    std::chrono::steady_clock::now() - start_time)
//                    .count();
//     avg_time += rtt;
//     if (dest)
//       dest_packets++;
//   }
// }

void traceroute(int sock_fd, const char *recipientIP) {
  int dest_packets = 0;
  pid_t pid = getpid();
  u_int16_t id = pid & 0xFFFF;

  for (int ttl = 1; ttl <= MAX_TTL && dest_packets < 3; ttl++) {
    double avg_time = 0.0;
    std::set<std::string> ips;
    int packets_received = 0;

    auto start_time = std::chrono::steady_clock::now();

    send_icmp_packets(sock_fd, ttl, recipientIP);

    while (packets_received < N_PACKETS) {
      auto elapsed_time = std::chrono::steady_clock::now() - start_time;
      int remaining_timeout_ms =
          TIMEOUT_MSECS -
          std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time)
              .count();
      if (remaining_timeout_ms <= 0)
        break;

      auto [ready, revent] = poll_socket(sock_fd, remaining_timeout_ms);
      if (ready == 0)
        break;

      if (ready > 0 && (revent == POLLIN)) {
        struct sockaddr_in sender;
        socklen_t sender_len = sizeof(sender);
        u_int8_t buffer[IP_MAXPACKET];

        ssize_t packet_len = recvfrom(sock_fd, buffer, IP_MAXPACKET, 0,
                                      (struct sockaddr *)&sender, &sender_len);
        if (packet_len < 0) {
          if (errno == EAGAIN || errno == EWOULDBLOCK) {
            break;
          } else {
            ERROR("recvfrom error");
            continue;
          }
        }

        struct ip *new_ip_header = (struct ip *)buffer;
        ssize_t new_ip_header_len = 4 * (ssize_t)(new_ip_header->ip_hl);
        struct icmp *new_icmp_header =
            (struct icmp *)(buffer + new_ip_header_len);

        char sender_ip_str[20];
        get_ip(sender, sender_ip_str, sizeof(sender_ip_str));

        int seq, packetId;
        if (new_icmp_header->icmp_type == ICMP_ECHOREPLY) {
          // std::cout<<dest_packets<<std::endl;
          if (dest_packets >= 3) {
            break;
          }
          seq = new_icmp_header->icmp_hun.ih_idseq.icd_seq;
          packetId = ntohs(new_icmp_header->icmp_hun.ih_idseq.icd_id);
          if (seq == ttl && id == packetId) {
            packets_received++;
            auto rtt = std::chrono::duration_cast<std::chrono::milliseconds>(
                           std::chrono::steady_clock::now() - start_time)
                           .count();
            avg_time += rtt;
            dest_packets++;
            get_ip(sender, sender_ip_str, sizeof(sender_ip_str));
            ips.insert(sender_ip_str);
          }

        } else if (new_icmp_header->icmp_type == ICMP_TIME_EXCEEDED) {
          struct ip *old_ip_header = (struct ip *)((char *)new_icmp_header + 8);
          ssize_t old_ip_header_len = 4 * (ssize_t)(old_ip_header->ip_hl);
          struct icmp *old_icmp_header =
              (struct icmp *)((char *)old_ip_header + old_ip_header_len);

          seq = old_icmp_header->icmp_hun.ih_idseq.icd_seq;
          packetId = ntohs(old_icmp_header->icmp_hun.ih_idseq.icd_id);

          if (seq == ttl && id == packetId) {
            packets_received++;
            auto rtt = std::chrono::duration_cast<std::chrono::milliseconds>(
                           std::chrono::steady_clock::now() - start_time)
                           .count();
            avg_time += rtt;
            char sender_ip_str[20];
            get_ip(sender, sender_ip_str, sizeof(sender_ip_str));
            ips.insert(sender_ip_str);
          }
        }
      }
    }

    print_ips(ttl, ips, packets_received ? avg_time / packets_received : 0.0,
              packets_received);
  }
}