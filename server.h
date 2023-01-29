#pragma once

class QueryServer {
public:
    QueryServer(const short int port);
    ~QueryServer();
    void run();
private:
    int listen_fd;
};