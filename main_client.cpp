#include "qclient/qclient.h"
#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <vector>

#define CONFIG "address.config"

std::vector<std::string> get_server_addresses(const std::string &configFile) {
  std::vector<std::string> addresses;
  std::ifstream config(configFile);

  if (!config) {
    std::cerr << "There is not config file!" << std::endl;
  }

  std::string line;
  while (std::getline(config, line)) {
    if (line.find("server_address") == 0) {
      // extract the value after the equal sign
      auto pos = line.find("=");
      if (pos != std::string::npos) {
        addresses.push_back(line.substr(pos + 1));
      }
    }
  }

  return addresses;
}


int main(int argc, char **argv) {
    std::string query = "";
    for (int i = 1; i < argc; ++i) {
        query += argv[i];
        if (i == (argc - 1)) {
            break;
        }
        query += " ";
    }
    std::vector<std::string> servers = get_server_addresses(CONFIG);
    for (auto server : servers) {
        QueryClient client = QueryClient(server.c_str(), 1234);
        std::string query_res = client.query(query.c_str());
        std::cout << "Query result from " << server << ": " << query_res << std::endl;
    }
}