#include "../include/handler.hpp"
#include "../include/server.http.hpp"
#include <iostream>
#include <spdlog/spdlog.h>

using namespace Web;

int main() {
  Server<HTTP> server(12345, 4);
  std::cout << "Server starting at port: 12345" << std::endl;
  start_server<Server<HTTP>>(server);
  spdlog::info("Welcome to spdlog!");
  return 0; // resources
}
