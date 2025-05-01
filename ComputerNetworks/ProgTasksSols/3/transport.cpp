#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "udp_client.h"
const SEG_SIZE = 1000;
const WINDOW_SIZE = 5;
const N = 10000;
bool recieved[N];
char window_data[N];

void update_window(int i, int n_segments){
    recieved[i] = true;
}

bool recieve_data(int port, char* ip, char* filename, int size){

    for (;;) {

        struct sockaddr_in 	sender;
        socklen_t sender_len = sizeof(sender);
        u_int8_t buffer[IP_MAXPACKET+1];

        ssize_t datagram_len = recvfrom(sock_fd, buffer, IP_MAXPACKET, 0, (struct sockaddr*)&sender, &sender_len);
        if (datagram_len < 0)
            ERROR("recvfrom error");

        char sender_ip_str[20];
        inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, sizeof(sender_ip_str));
        printf("Received UDP packet from IP address: %s, port: %d\n", sender_ip_str, ntohs(sender.sin_port));
        if ( (ntohs(sender.sin_port) == port) && (strcmp(sender_ip_str, ip) == 0) ) {
            // OK, packet is from the correct IP and port
            // zapisz do okna
            return true;
        } else {
            // Wrong sender, ignore
            continue;
        }


        buffer[datagram_len] = 0;
        printf("%ld-byte message: +%s+\n", datagram_len, (char*)buffer);

        char* reply = "Thank you!";
        size_t reply_len = strlen(reply);
        if (sendto(sock_fd, reply, reply_len, 0, (struct sockaddr*)&sender, sender_len) != reply_len)
            ERROR("sendto error");

        assert(fflush(stdout) == 0);
    }
}
void main_logic(char* ip, int port, char* filename, int size) {
    char request[100];

    for (int i = 0; i < 100; i++) {
        std::string str = "GET 0 " + std::to_string(offset) + " " + std::to_string(size);
        send_request(str.c_str(), ip, port, filename, size);
        recieve_data(port, ip, filename,size);
    }
}

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments are provided
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <ip> <port> <filename> <size>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char* ip = argv[1];
    int port = atoi(argv[2]);
    char* filename = argv[3];
    int size = atoi(argv[4]);

    printf("IP: %s\n", ip);
    printf("Port: %d\n", port);
    printf("Filename: %s\n", filename);
    printf("Size: %d\n", size);

    for (int i = 0; i < 100; i++){
        send_request("GET 0 700\n",ip,port,filename,size);
        recieve_data();
    }

    return 0;
}