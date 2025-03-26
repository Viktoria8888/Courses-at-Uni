// Viktoriia Kashpruk 337014
#ifndef ICMP_UTILS_H
#define ICMP_UTILS_H
#include <netinet/ip_icmp.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <sys/time.h>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
u_int16_t compute_icmp_checksum(const void *buff, int length);
void ERROR(const char *str);
void get_ip(struct sockaddr_in sender, char *sender_ip_str, size_t size);
void print_ips(int n, const std::set<std::string> &ips, double avg_time, int packets_received);
const int TIMEOUT_MSECS = 1000;
const int N_PACKETS = 3;
const int MAX_TTL = 30;
// extern const char* recipientIP;
#endif