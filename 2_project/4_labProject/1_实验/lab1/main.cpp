#include "stdafx.h"
#include <WinSock2.h>
#include <Windows.h>
#include <handleapi.h>
#include <inaddr.h>
#include <iostream>
#include <process.h>
#include <stdio.h>
#include <string.h>
#include <synchapi.h>
#include <winsock.h>

// (1) 设计并实现一个基本 HTTP 代理服务器.要求在指定端口(例如8080)接收来自客户的
// HTTP 请求并且根据其中的 URL 地址访问该地址 所指向的 HTTP
// 服务器(原服务器),接收 HTTP
// 服务器的响应报文,并将响应报文转发给对应的客户进行浏览.<br>

// (2) 设计并实现一个支持 Cache 功能的HTTP 代理服务器.要求能缓
// 存原服务器响应的对象,并能够通过修改请求报文(添加 if-modified-since
// 头行),向原服务器确认缓存对象是否是最新版本.(选作内容,加分项
// 目,可以当堂完成或课下完成)

// (3) 扩展 HTTP 代理服务器,支持如下功能:(选作内容,加分项目,
// 可以当堂完成或课下完成) a) 网站过滤:允许/不允许访问某些网站; b)
// 用户过滤:支持/不支持某些用户访问外部网站; c)
// 网站引导:将用户对某个网站的访问引导至一个模拟网站(钓 鱼).

#pragma comment(lib, "ws2_32.lib")

#define MAXSIZE 65507 // 发送数据报文的最大长度
#define HTTP_PORT 80  // http服务器端口

// Http 头部数据结构
struct HttpHeader {
  char method[4];         // POST or GET
  char url[1024];         // url
  char host[1024];        // host
  char cookie[1024 * 10]; // cookie
  HttpHeader() { ZeroMemory(this, sizeof(HttpHeader)); }
};

BOOL InitSocket();
void ParseHttpHead(char *buffer, HttpHeader *httpHeader);
BOOL ConnectToServer(SOCKET *serverSocket, char *host);
unsigned int __stdcall ProxyThread(LPVOID lpParameter);

SOCKET ProxyServer;
sockaddr_in ProxyServerAddr;

const int ProxyPort = 10240;

const int ProxyThreadMaxNum = 20;
HANDLE ProxyThreadHandle[ProxyThreadMaxNum] = {0};
DWORD ProxyThreadDW[ProxyThreadMaxNum] = {0};

struct ProxyParam {
  SOCKET clientSocket;
  SOCKET serverSocket;
};

int main() {
  std::cout << "socket init failed" << std::endl;
  if (!InitSocket()) {
    std::cout << "socket init failed" << std::endl;
    return -1;
  }
  std::cout << "init success, listen port: " << ProxyPort << std::endl;
  SOCKET acceptSocket = INVALID_SOCKET;
  ProxyParam *lpProxyParam;
  HANDLE hThread;
  DWORD dwThreadID;
  while (1) {
    acceptSocket = accept(ProxyServer, NULL, NULL);
    lpProxyParam = new ProxyParam;
    if (!lpProxyParam) {
      continue;
    }
    lpProxyParam->clientSocket = acceptSocket;
    hThread = (HANDLE)_beginthreadex(nullptr, 0, &ProxyThread,
                                     (LPVOID)lpProxyParam, 0, 0);
    CloseHandle(hThread);
    Sleep(200);
  }
  closesocket(ProxyServer);
  WSACleanup();
  return 0;
}

BOOL InitSocket() {
  WORD wVersionRequested;
  WSADATA wsaData;
  int err;
  wVersionRequested = MAKEWORD(2, 2);
  err = WSAStartup(wVersionRequested, &wsaData);
  if (err != 0) {
    std::cout << "init winsock failed, error code: " << WSAGetLastError()
              << std::endl;
    return FALSE;
  }
  if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
    std::cout << "winsock version error" << std::endl;
    WSACleanup();
    return FALSE;
  }
  ProxyServer = socket(AF_INET, SOCK_STREAM, 0);
  if (ProxyServer == INVALID_SOCKET) {
    std::cout << "create socket failed, error code: " << WSAGetLastError()
              << std::endl;
    return FALSE;
  }
  ProxyServerAddr.sin_family = AF_INET;
  ProxyServerAddr.sin_port = htons(ProxyPort);
  ProxyServerAddr.sin_addr.S_un.S_addr = INADDR_ANY;
  if (bind(ProxyServer, (SOCKADDR *)&ProxyServerAddr, sizeof(SOCKADDR)) ==
      SOCKET_ERROR) {
    std::cout << "bind port " << ProxyPort << " failed" << std::endl;
    return FALSE;
  }
  if (listen(ProxyServer, SOMAXCONN) == SOCKET_ERROR) {
    std::cout << "listen port " << ProxyPort << " failed" << std::endl;
    return FALSE;
  }
  return TRUE;
}

unsigned int __stdcall ProxyThread(LPVOID lpParameter) {
  char Buffer[MAXSIZE];
  char *CacheBuffer;
  ZeroMemory(&Buffer, sizeof(Buffer));
  SOCKADDR_IN clientAddr;
  int length = sizeof(SOCKADDR_IN);
  int recvSize;
  int ret;
  recvSize =
      recv(((ProxyParam *)lpParameter)->clientSocket, Buffer, MAXSIZE, 0);
  if (recvSize <= 0) {
    std::cout << "recv failed" << std::endl;
    goto error;
  }
  HttpHeader *httpHeader = new HttpHeader();
  CacheBuffer = new char[recvSize + 1];
  memcpy(CacheBuffer, Buffer, recvSize);
  ParseHttpHead(CacheBuffer, httpHeader);
  delete CacheBuffer;
  if (!ConnectToServer(&((ProxyParam *)lpParameter)->serverSocket,
                       httpHeader->host)) {
    std::cout << "connect to server failed" << std::endl;
    goto error;
  }
  std::cout << "proxy" << httpHeader->host << "success" << std::endl;
  ret = send(((ProxyParam *)lpParameter)->serverSocket, Buffer,
             strlen(Buffer) + 1, 0);
  recvSize =
      recv(((ProxyParam *)lpParameter)->serverSocket, Buffer, MAXSIZE, 0);
  if (recvSize <= 0) {
    std::cout << "recv from server failed" << std::endl;
    goto error;
  }
  ret = send(((ProxyParam *)lpParameter)->clientSocket, Buffer, sizeof(Buffer),
             0);
  if (recvSize <= 0) {
    std::cout << "send to client failed" << std::endl;
    goto error;
  }

error:
  std::cout << "close socket" << std::endl;
  Sleep(200);
  closesocket(((ProxyParam *)lpParameter)->clientSocket);
  closesocket(((ProxyParam *)lpParameter)->serverSocket);
  delete lpParameter;
  _endthreadex(0);
  return 0;
}

void ParseHttpHeader(const char *bufferConst, HttpHeader *httpHeader) {
  char *p;
  const char *delim = "\r\n";
  p = strtok_s(buffer, delim);
  if (p[0] == 'G') {
    memcpy(httpHeader->method, "GET", 3);
    memcpy(httpHeader->url, &p[4], strlen(p) - 13);
  } else if (p[0] == 'P') {
    memcpy(httpHeader->method, "POST", 4);
    memcpy(httpHeader->url, &p[5], strlen(p) - 14);
  }
  p = strtok_s(NULL, delim);
  while (p) {
    switch (p[0]) {
    case 'H':
      memcpy(httpHeader->host, &p[6], strlen(p) - 6);
      break;
    case 'C':
      if (strlen(p) > 8) {
        char header[8];
        ZeroMemory(header, sizeof(header));
        memcpy(header, p, 6);
        if (!strcmp(header, "Cookie")) {
          memcpy(httpHeader->cookie, &p[8], strlen(p) - 8);
        }
      }
      break;
    default:
      break;
    }
    p = strtok_s(NULL, delim);
  }
}

BOOL ConnectToServer(SOCKET *serverSocket, const char *host) {
  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(HTTP_PORT);
  HOSTENT *hostent = gethostbyname(host);
  if (!hostent)
    return FALSE;
  in_addr InAddr = *((in_addr *)*hostent->h_addr_list);
  serverAddress.sin_addr.s_addr = inet_addr(inet_ntoa(InAddr));
  *serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (*serverSocket == INVALID_SOCKET)
    return FALSE;
  if (connect(*serverSocket, (SOCKADDR *)&serverAddress,
              sizeof(serverAddress)) == SOCKET_ERROR) {
    closesocket(*serverSocket);
    return FALSE;
  }
  return TRUE;
}

// #define INVILID_WEBSITE "http://www.qq.com/" // �����ε���վ
// #define FISHING_WEB_SRC "http://today.hit.edu.cn/" // �����Դ���?
// #define FISHING_WEB_DEST "http://jwts.hit.edu.cn/" // �����Ŀ�����?
// #define FISHING_WEB_HOST "jwts.hit.edu.cn" // ����Ŀ�ĵ�ַ��������
