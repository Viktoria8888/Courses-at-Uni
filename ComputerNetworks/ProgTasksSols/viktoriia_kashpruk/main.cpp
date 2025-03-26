// Viktoriia Kashpruk 337014
#include "icmp_utils.h"
#include "traceroute.h"

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <destination IP>" << std::endl;
    return 1;
  }
  struct sockaddr_in sa;
  int result = inet_pton(AF_INET, argv[1], &(sa.sin_addr));
  if (result != 1) {
    std::cout<< "Invalid IP address: " << argv[1] << std::endl;
    return 1;
  }
  int sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  if (sock_fd < 0) {
    ERROR("socket error");
    return 1;
  }

  const char *recipientIP = argv[1];
  traceroute(sock_fd, recipientIP);
  close(sock_fd);
  return 0;
}
