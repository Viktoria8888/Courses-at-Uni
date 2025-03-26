// Viktoriia Kashpruk 337014
#ifndef ICMP_SEND_H
#define ICMP_SEND_H

void send_icmp_packet(int sock_fd, int ttl, int seq, const char* recipientIP);
void send_icmp_packets(int sock_fd, int ttl, const char *recipientIP);

#endif