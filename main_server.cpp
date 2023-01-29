#include "server.h"

int main() {
    QueryServer server = QueryServer(1234);
    server.run();
}