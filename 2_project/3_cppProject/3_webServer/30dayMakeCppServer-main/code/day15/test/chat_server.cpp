#include <iostream>
#include <map>
#include "Connection.h"
#include "EventLoop.h"
#include "Server.h"
#include "Socket.h"

int main() {
  std::map<int, Connection *> clients;

  EventLoop *loop = new EventLoop();
  Server *server = new Server(loop);

  server->NewConnect(
      [&](Connection *conn) {
      int clnt_fd = conn->GetSocket()->GetFd();
      std::cout << "New connection fd: " << clnt_fd << '\n';
      clients[clnt_fd] = conn;
        for(auto &each : clients){
        Connection *client = each.second;
        client->Send(conn->ReadBuffer());
      }
  });

  server->OnMessage([&](Connection *conn) {
    std::cout << "Message from client " << conn->ReadBuffer() << '\n';
    for (auto &each : clients) {
      Connection *client = each.second;
      client->Send(conn->ReadBuffer());
    }
  });

  loop->Loop();
  return 0;
}


