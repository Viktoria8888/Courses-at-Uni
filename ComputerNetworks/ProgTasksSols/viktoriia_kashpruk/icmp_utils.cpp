// Viktoriia Kashpruk 337014
#include "icmp_utils.h"
u_int16_t compute_icmp_checksum(const void *buff, int length) {
  const u_int16_t *ptr = (const u_int16_t *)buff;
  u_int32_t sum = 0;
  assert(length % 2 == 0);
  for (; length > 0; length -= 2)
    sum += *ptr++;
  sum = (sum >> 16U) + (sum & 0xffffU);
  return (u_int16_t)(~(sum + (sum >> 16U)));
}

void ERROR(const char *str) {
  std::cerr << str << ": " << strerror(errno) << std::endl;
  exit(EXIT_FAILURE);
  
}


void get_ip(struct sockaddr_in sender, char *sender_ip_str, size_t size) {
  inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, size);
}

void print_ips(int n, const std::set<std::string> &ips, double avg_time, int packets_received) {
  std::cout << n << ". ";
  if (ips.empty()) {
    std::cout << "*";
  } else {
    for (const auto &ip : ips) {
      std::cout << ip << " ";
    }
    if (packets_received < N_PACKETS) {
      std::cout << "???";
    } else {
      std::cout << avg_time << " ms";
    }
  }
  std::cout << std::endl;
}
