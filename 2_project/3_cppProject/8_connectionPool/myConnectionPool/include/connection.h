#pragma once

#include <mysql.h>
#include <string>

class connection {
public:
  connection() {}
  ~connection() = default;

  connection(const connection &) = default;
  connection &operator=(const connection &) = default;
  connection(connection &&) = default;
  connection &operator=(connection &&) = default;

  bool connect(std::string ip, unsigned char port, std::string user,
               std::string password, std::string dbName);

  bool update(std::string sql);

  void myFunction();
};