#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>


void ERROR(const char* str)
{
    fprintf(stderr, "%s: %s\n", str, strerror(errno));  // NOLINT(*-err33-c)
    exit(EXIT_FAILURE);
}
void write_to_file(const char* filename, const char* data, int size) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open error");
        exit(EXIT_FAILURE);
    }

    ssize_t written = write(fd, data, size);
    if (written != size) {
        perror("write error");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);
}
int send_request(char* req, char* ip, int port, char* name, int size){
    printf("Sending request: %s\n", req);

    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0)
        ERROR("socket error");

    struct sockaddr_in server_address = { 0 };
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_address.sin_addr);

    char* message = req;
    size_t message_len = strlen(message);
    ssize_t sent_bytes = sendto(sock_fd, message, message_len, 0, (struct sockaddr*)&server_address, sizeof(server_address));
    if (sent_bytes != message_len) {
        fprintf(stderr, "Error: Only %zd bytes sent, expected %zu\n", sent_bytes, message_len);
        ERROR("sendto error");
    } else {
        printf("Message sent successfully.\n");
    }


    close(sock_fd);
    return EXIT_SUCCESS;
}


