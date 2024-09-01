#include <iostream>
#include "pine.h"

int main() {
  TcpServer *server = new TcpServer();

  Signal::signal(SIGINT, [&] {
    delete server;
    std::cout << "\nServer exit!" << '\n';
    exit(0);
  });

  server->onConnect([](Connection *conn) { std::cout << "New connection fd: " << conn->socket()->fd() << '\n'; });

  server->onRecv([](Connection *conn) {
    std::cout << "Message from client " << conn->read_buf()->c_str() << '\n';
    conn->Send(conn->read_buf()->c_str());
  });

  server->Start();

  delete server;
  return 0;
}
