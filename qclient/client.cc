#include "client.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

QueryClient::QueryClient(const char* server_ip, const short int port) {
    this->connfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->connfd < 0) {
        perror("socket error");
    }

    struct sockaddr_in server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = ntohs(port);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    int rv = connect(this->connfd, (struct sockaddr *)&server_addr, (socklen_t)sizeof(server_addr));
    if (rv < 0) {
        perror("connect error");
    }
}

QueryClient::~QueryClient() {
    close(this->connfd);
}

std::string QueryClient::query(const char* query) {
    ssize_t n = write(this->connfd, query, strlen(query));
    if (n <= 0) {
        perror("write error");
    }
    char rbuf[64] = {};
    while (n > 0) {
        n = read(this->connfd, rbuf, sizeof(rbuf));
        std::cout << rbuf << std::endl;
    }
    return (std::string) rbuf;
}
