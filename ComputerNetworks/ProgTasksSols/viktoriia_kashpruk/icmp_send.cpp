// Viktoriia Kashpruk 337014
#include "icmp_utils.h"


void send_icmp_packet(int sock_fd, int ttl, int seq, const char* recipientIP) {
  pid_t pid = getpid();
  u_int16_t id = pid & 0xFFFF;
  struct icmp header;
  header.icmp_type = ICMP_ECHO;
  header.icmp_code = 0;
  header.icmp_hun.ih_idseq.icd_id = htons(id);
  header.icmp_hun.ih_idseq.icd_seq = seq;
  header.icmp_cksum = 0;
  header.icmp_cksum = compute_icmp_checksum((u_int16_t *)&header, sizeof(header));

  struct sockaddr_in recipient;
  memset(&recipient, 0, sizeof(recipient));
  recipient.sin_family = AF_INET;
  inet_pton(AF_INET, recipientIP, &recipient.sin_addr);

  if (setsockopt(sock_fd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
    ERROR("setsockopt error");


  ssize_t bytes_sent = sendto(sock_fd, &header, sizeof(header), 0, (struct sockaddr *)&recipient, sizeof(recipient));
  if (bytes_sent < 0)
    ERROR("sendto error");


}

void send_icmp_packets(int sock_fd, int ttl, const char *recipientIP) {
  for (int i = 0; i < N_PACKETS; i++) {
      send_icmp_packet(sock_fd, ttl, ttl, recipientIP);
  }
}

