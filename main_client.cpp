#include "qclient/qclient.h"
#include <iostream>
#include <string>

int main(int argc, char **argv) {
    std::string query = "";
    for (int i = 1; i < argc; ++i) {
        query += argv[i];
        if (i == (argc - 1)) {
            break;
        }
        query += " ";
    }
    std::cout << query << std::endl;
    QueryClient client = QueryClient("127.0.0.1", 1234);
    std::string query_res = client.query(query.c_str());
}