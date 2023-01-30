#include "qclient/client.h"
#include <iostream>
#include <string>

int main() {
    QueryClient client = QueryClient("127.0.0.1", 1234);
    std::string query_res = client.query("grep -Ec lorem test");
    std::cout << "Query Result is: " << query_res << std::endl;
}