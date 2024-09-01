#include "../include/handler.hpp"
#include "../include/server.https.hpp"

#include <iostream>

using namespace Web;

int main() {
  // HTTPS server runs in port 12345, enable 4 threads
  // Use certificates for security
  Server<HTTPS> server(12345, 4, "server.crt", "server.key");
  std::cout << "Server starting at port: 12345" << '\n';
  start_server<Server<HTTPS>>(server);
  return 0;
}
