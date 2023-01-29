#pragma once

#include <string>
#include <sys/socket.h>

class QueryClient {
public:
    QueryClient(const char* server_ip, const short int port);
    ~QueryClient();
    std::string query(const char* query);
private:
    int connfd;
};