#include "server.h"
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>

static void err_msg(const char* text) {
    std::cerr << text << std::endl;
}

static void msg(const char* text) {
    std::cout << text << std::endl;
}

QueryServer::QueryServer(const short int port) {
    this->listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->listen_fd < 0) {
        perror("socket error");
    }

    // reuse address
    int val = 1;
    setsockopt(this->listen_fd, SOL_SOCKET, SO_REUSEADDR, (void *)&val, sizeof(val));

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(port);
    addr.sin_addr.s_addr = ntohl(0);
    
    // bind
    int rv = bind(this->listen_fd, (struct sockaddr *)&addr, sizeof(addr));
    if (rv < 0) {
        perror("bind erorr");
    }

    // listen
    rv = listen(this->listen_fd, SOMAXCONN);
    if (rv < 0) {
        perror("listen error");
    }
}

QueryServer::~QueryServer() {
    close(this->listen_fd);
}

void QueryServer::run() {
    msg("Server started.");
    while (true) {
        // accept new connections
        struct sockaddr_in client_addr = {};
        socklen_t len = sizeof(client_addr);
        int connfd = accept(this->listen_fd, (struct sockaddr *)&client_addr, (socklen_t*)&len);
        if (connfd < 0) {
            perror("accept error");
        }

        char rbuf[64] = {};
        ssize_t n = read(connfd, rbuf, sizeof(rbuf));
        if (n <= 0) {
            err_msg("read");
            continue;
        }

        char wbuf[] = "Hello from server";
        n = write(connfd, wbuf, strlen(wbuf));
        if (n <= 0) {
            err_msg("read");
            continue;
        }
    }
}