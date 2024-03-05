//#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>
#include <process.h>
#include <string.h>

// Codeblocks ʹ�õ��� MingGW
// ������,MingGW��֧��#pragma comment(lib,"Ws2_32.lib")
// ��д�� �������Ǿ�̬���� Ws2_32.lib ��,
// ������������,���� -lws2_32 �� -lwsock32
// #pragma comment(lib,"Ws2_32.lib")

#define MAXSIZE 65507 // �������ݱ��ĵ���󳤶�?
#define HTTP_PORT 80 // http �������˿�

#define INVILID_WEBSITE "http://www.qq.com/" // �����ε���վ
#define FISHING_WEB_SRC "http://today.hit.edu.cn/" // �����Դ���?
#define FISHING_WEB_DEST                                                       \
  "http://jwts.hit.edu.cn/" // �����Ŀ�����?
#define FISHING_WEB_HOST                                                       \
  "jwts.hit.edu.cn" // ����Ŀ�ĵ�ַ��������

// Http ��Ҫͷ������
struct HttpHeader{
  char method[4]; // POST ���� GET��ע����ЩΪ
                  // CONNECT����ʵ���� ������
  char url[1024];         // �����? url
  char host[1024];        // Ŀ������
  char cookie[1024 * 10]; // cookie
  HttpHeader() { ZeroMemory(this, sizeof(HttpHeader)); }
};

BOOL InitSocket();
void ParseHttpHead(char *buffer,HttpHeader * httpHeader);
BOOL ConnectToServer(SOCKET *serverSocket,char *host);
unsigned int __stdcall ProxyThread(LPVOID lpParameter);
boolean ParseDate(char *buffer, char *field, char *tempDate);
void makeNewHTTP(char *buffer, char *value);
void makeFilename(char *url, char *filename);
void makeCache(char *buffer, char *url);
void getCache(char *buffer, char *filename);

// ������ز���?
SOCKET ProxyServer;
sockaddr_in ProxyServerAddr;
const int ProxyPort = 10240;

// ������ز���?
boolean haveCache = FALSE;
boolean needCache = TRUE;
char * strArr[100];

// �����µ����Ӷ�ʹ�����߳̽��д��������̵߳�Ƶ���Ĵ����������ر��˷���Դ
// ����ʹ���̳߳ؼ�����߷�����Ч��?
// const int ProxyThreadMaxNum = 20;
// HANDLE ProxyThreadHandle[ProxyThreadMaxNum] = {0};
// DWORD ProxyThreadDW[ProxyThreadMaxNum] = {0};

struct ProxyParam{
    SOCKET clientSocket;
    SOCKET serverSocket;
};

int main(int argc, char* argv[]) {
  printf("������������������\n");
  printf("��ʼ��...\n");
  if (!InitSocket()) {
    printf("socket ��ʼ��ʧ��\n");
    return -1;
  }
    printf("�����������������У�����"
           "���˿� %d\n",
           ProxyPort);
    SOCKET acceptSocket = INVALID_SOCKET;
    ProxyParam *lpProxyParam;
    HANDLE hThread;
    // �������������ϼ���
    while(true){
        acceptSocket = accept(ProxyServer,NULL,NULL);
        lpProxyParam = new ProxyParam;
        if(lpProxyParam == NULL){
            continue;
        }
        lpProxyParam->clientSocket = acceptSocket;
        hThread = (HANDLE)_beginthreadex(NULL, 0, &ProxyThread,(LPVOID)lpProxyParam, 0, 0);
        CloseHandle(hThread);
        Sleep(200);
    }
    closesocket(ProxyServer);
    WSACleanup();
    return 0;
}

//************************************
// Method:    InitSocket
// FullName:  InitSocket
// Access:    public
// Returns:   BOOL
// Qualifier: ��ʼ���׽���
//************************************
BOOL InitSocket(){
  // �����׽��ֿ�(����)
  WORD wVersionRequested;
  WSADATA
      wsaData; // WSADATA�ṹ������Ҫ������ϵͳ��֧�ֵ�Winsock�汾��Ϣ
  // �׽��ּ���ʱ������ʾ
  int err;
  // �汾 2.2
  wVersionRequested = MAKEWORD(2, 2);
  // ���� dll �ļ� Scoket ��
  err = WSAStartup(wVersionRequested, &wsaData);
  if (err != 0) {
    // �Ҳ��� winsock.dll
    printf("���� winsock ʧ�ܣ���������?: %d\n",
           WSAGetLastError());
    return FALSE;
  }
    // LOBYTE()�õ�һ��16bit����ͣ����ұߣ��Ǹ��ֽ�?
    // HIBYTE()�õ�һ��16bit����ߣ�����ߣ��Ǹ��ֽ�
    // �жϴ򿪵��Ƿ���2.2�汾
    if(LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) !=2)   {
      printf("�����ҵ���ȷ�� winsock �汾\n");
      WSACleanup();
      return FALSE;
    }
    // AF_INET,PF_INET	IPv4 InternetЭ��
    // SOCK_STREAM
    // Tcp���ӣ��ṩ���л��ġ��ɿ��ġ�˫�����ӵ��ֽ�����֧�ִ������ݴ���
    ProxyServer = socket(AF_INET, SOCK_STREAM, 0);
    if(INVALID_SOCKET == ProxyServer){
      printf("�����׽���ʧ�ܣ��������Ϊ��"
             "?%d\n",
             WSAGetLastError());
      return FALSE;
    }
    ProxyServerAddr.sin_family = AF_INET;
    ProxyServerAddr.sin_port = htons(
        ProxyPort); // �����ͱ����������ֽ�˳��ת��������ֽ�˳��?

    // �����û�
    // ProxyServerAddr.sin_addr.S_un.S_addr = INADDR_ANY;
    ProxyServerAddr.sin_addr.S_un.S_addr = inet_addr(
        "127.0.0.1"); // �������û��ɷ��ʷ�����
    // ProxyServerAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.2");
    // //�����û�
    if(bind(ProxyServer,(SOCKADDR*)&ProxyServerAddr,sizeof(SOCKADDR)) == SOCKET_ERROR){
      printf("���׽���ʧ��\n");
      return FALSE;
    }
    if(listen(ProxyServer, SOMAXCONN) == SOCKET_ERROR){
      printf("�����˿�%d ʧ��", ProxyPort);
      return FALSE;
    }
    return TRUE;
}
//************************************
// Method:    ProxyThread
// FullName:  ProxyThread
// Access:    public
// Returns:   unsigned int __stdcall
// Qualifier: �߳�ִ�к���
// Parameter: LPVOID lpParameter
//************************************
unsigned int __stdcall ProxyThread(LPVOID lpParameter){
    char Buffer[MAXSIZE], fileBuffer[MAXSIZE];
    char *CacheBuffer;
    HttpHeader* httpHeader = new HttpHeader();
    ZeroMemory(Buffer,MAXSIZE);
    SOCKADDR_IN clientAddr;
    int length = sizeof(SOCKADDR_IN);
    int recvSize;
    int ret;
    recvSize = recv(((ProxyParam *)lpParameter)->clientSocket,Buffer,MAXSIZE,0);
    /*if(recvSize <= 0){
        goto error;
    }*/
    CacheBuffer = new char[recvSize + 1];
    ZeroMemory(CacheBuffer, recvSize + 1);
    memcpy(CacheBuffer, Buffer, recvSize);

    // ����http�ײ�
    ParseHttpHead(CacheBuffer, httpHeader);

    // ����
    char *DateBuffer;
    DateBuffer = (char*)malloc(MAXSIZE);
	ZeroMemory(DateBuffer, strlen(Buffer) + 1);
	memcpy(DateBuffer, Buffer, strlen(Buffer) + 1);
	//printf("DateBuffer: \n%s\n", DateBuffer);
	char filename[100];
	ZeroMemory(filename, 100);
	makeFilename(httpHeader->url, filename);
	//printf("filename : %s\n", filename);
	char *field = "Date";
        char date_str[30]; // �����ֶ�Date��ֵ
        ZeroMemory(date_str, 30);
	ZeroMemory(fileBuffer, MAXSIZE);
	FILE *in;
	if ((in = fopen(filename, "rb")) != NULL) {
          printf("\n�л���\n");
          fread(fileBuffer, sizeof(char), MAXSIZE, in);
          fclose(in);
          ParseDate(fileBuffer, field, date_str);
          printf("date_str:%s\n", date_str);
          makeNewHTTP(Buffer, date_str);
          haveCache = TRUE;
          goto success;
	}

        // ��վ���ˣ�����һ����վ
        if (strcmp(httpHeader->url, INVILID_WEBSITE) == 0) {
          printf("\n=====================================\n\n");
          printf("-------------Sorry!!!����վ�ѱ�����------"
                 "--"
               "--------\n");
          goto error;
    }
    // ��վ��������������ַת��������վ
    if (strstr(httpHeader->url, FISHING_WEB_SRC) != NULL) {
      printf("\n=====================================\n\n");
      printf("-------------�Ѵ�Դ��ַ��%s ת�� "
             "Ŀ����ַ ��%s ----------------\n",
             FISHING_WEB_SRC, FISHING_WEB_DEST);
      // ����ΪʲôҪ��һ����Ҳ��֪����ֻ��˵��ɲ���һ�����?
      // ֻҪ������ԭ���ĳ��ȾͿ���
      memcpy(httpHeader->host, FISHING_WEB_HOST, strlen(FISHING_WEB_HOST) + 1);
      memcpy(httpHeader->url, FISHING_WEB_DEST, strlen(FISHING_WEB_DEST));
      // memcpy(httpHeader->host, "jwts.hit.edu.cn", strlen("jwts.hit.edu.cn"));
      // //���в������ã���֪��Ϊʲô������
    }
    delete CacheBuffer;
    delete DateBuffer;

success:
    if(!ConnectToServer(&((ProxyParam *)lpParameter)->serverSocket,httpHeader->host)) {
      printf("����Ŀ�������ʧ�ܣ�����\n");
      goto error;
    }
    printf("������������ %s �ɹ�\n",
           httpHeader->host);
    // ���ͻ��˷��͵� HTTP
    // ���ݱ���ֱ��ת����Ŀ�������?
    ret = send(((ProxyParam *)lpParameter)->serverSocket,Buffer,strlen(Buffer) + 1,0);
    // �ȴ�Ŀ���������������?
    recvSize = recv(((ProxyParam *)lpParameter)->serverSocket,Buffer,MAXSIZE,0);
    if(recvSize <= 0){
      printf("����Ŀ�������������ʧ�ܣ��"
             "���\n");
      goto error;
    }
    // �л���ʱ���жϷ��ص�״̬���Ƿ���304�������򽫻�������ݷ��͸��ͻ���?
    if (haveCache == TRUE) {
      getCache(Buffer, filename);
	}
	if (needCache == TRUE) {
          makeCache(Buffer, httpHeader->url); // ���汨��
        }
        // ��Ŀ����������ص�����ֱ��ת�����ͻ���?
        ret = send(((ProxyParam *)lpParameter)->clientSocket, Buffer,
                   sizeof(Buffer), 0);

// ������
error:
  printf("�ر��׽���\n");
  delete Buffer;
  delete fileBuffer;
  delete filename;
  Sleep(200);
  closesocket(((ProxyParam *)lpParameter)->clientSocket);
  closesocket(((ProxyParam *)lpParameter)->serverSocket);
  delete lpParameter;
  _endthreadex(0);
  return 0;
}
//************************************
// Method:    ParseHttpHead
// FullName:  ParseHttpHead
// Access:    public
// Returns:   void
// Qualifier: ���� TCP �����е� HTTP ͷ��
// Parameter: char * buffer
// Parameter: HttpHeader * httpHeader
//************************************
void ParseHttpHead(char *buffer,HttpHeader * httpHeader){
    char *p;
    const char * delim = "\r\n";
    p = strtok(
        buffer,
        delim); // ��һ�ε��ã���һ������Ϊ���ֽ���ַ���?
    // ��ȡ��һ��
    // printf("%s\n",p);
    if(p[0] == 'G'){
      // GET ��ʽ
      memcpy(httpHeader->method, "GET", 3);
      memcpy(httpHeader->url, &p[4],
             strlen(p) -
                 13); //'Get' �� 'HTTP/1.1' ��ռ 3 �� 8
                      //�����ټ������ո�һ��13��
    }
    else if(p[0] == 'P'){
      // POST ��ʽ
      memcpy(httpHeader->method, "POST", 4);
      memcpy(httpHeader->url, &p[5],
             strlen(p) -
                 14); //'Post' �� 'HTTP/1.1' ��ռ 4 �� 8
                      //�����ټ������ո�һ��14��
    }
    printf("���ʵ�url�� �� %s\n", httpHeader->url);
    p = strtok(NULL, delim); // �ڶ��ε��ã���Ҫ����һ��������Ϊ
                             // NULL
    while(p){
        switch(p[0]){
            case 'H'://Host
                memcpy(httpHeader->host,&p[6],strlen(p) - 6);
                break;
            case 'C'://Cookie
                if(strlen(p) > 8){
                    char header[8];
                    ZeroMemory(header,sizeof(header));
                    memcpy(header,p,6);
                    if(!strcmp(header,"Cookie")){
                        memcpy(httpHeader->cookie,&p[8],strlen(p) -8);
                    }
                }
                break;
            default:
                break;
        }
        p = strtok(NULL,delim);
    }
}
//************************************
// Method:    ConnectToServer
// FullName:  ConnectToServer
// Access:    public
// Returns:   BOOL
// Qualifier:
// ������������Ŀ��������׽��֣�������?
// Parameter: SOCKET * serverSocket
// Parameter: char * host
//************************************
BOOL ConnectToServer(SOCKET *serverSocket,char *host){
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(HTTP_PORT);
    HOSTENT *hostent = gethostbyname(host);
    if(!hostent){
        return FALSE;
    }
    in_addr Inaddr = *( (in_addr*) *hostent->h_addr_list);
    serverAddr.sin_addr.s_addr = inet_addr(inet_ntoa(Inaddr));
    *serverSocket = socket(AF_INET,SOCK_STREAM,0);
    if(*serverSocket == INVALID_SOCKET){
        return FALSE;
    }
    if(connect(*serverSocket,(SOCKADDR *)&serverAddr,sizeof(serverAddr)) == SOCKET_ERROR){
        closesocket(*serverSocket);
        return FALSE;
    }
    return TRUE;
}

// ����HTTPͷ����field�ֶΣ����������field�򷵻�true������ȡ����
boolean ParseDate(char *buffer, char *field, char *tempDate) {
	char *p, *ptr, temp[5];
	//*field = "If-Modified-Since";
	const char *delim = "\r\n";
	ZeroMemory(temp, 5);
	p = strtok(buffer, delim);
	//printf("%s\n", p);
	int len = strlen(field) + 2;
	while (p) {
		if (strstr(p, field) != NULL) {
			memcpy(tempDate, &p[len], strlen(p) - len);
			//printf("tempDate: %s\n", tempDate);
			return TRUE;
		}
		p = strtok(NULL, delim);
	}
	return TRUE;
}

// ����HTTP������
void makeNewHTTP(char *buffer, char *value) {
	const char *field = "Host";
	const char *newfield = "If-Modified-Since: ";
	//const char *delim = "\r\n";
	char temp[MAXSIZE];
	ZeroMemory(temp, MAXSIZE);
	char *pos = strstr(buffer, field);
    int i = 0;
	for (i = 0; i < strlen(pos); i++) {
		temp[i] = pos[i];
	}
	*pos = '\0';
        while (*newfield != '\0') { // ����If-Modified-Since�ֶ�
          *pos++ = *newfield++;
        }
        while (*value != '\0') {
		*pos++ = *value++;
	}
	*pos++ = '\r';
	*pos++ = '\n';
	for (i = 0; i < strlen(temp); i++) {
		*pos++ = temp[i];
	}
}

// ����url�����ļ���
void makeFilename(char *url, char *filename) {
	while (*url != '\0') {
		if (*url != '/' && *url != ':' && *url != '.') {
			*filename++ = *url;
		}
		url++;
	}
    strcat(filename, ".txt");
}

// ���л���
void makeCache(char *buffer, char *url) {
	char *p, *ptr, num[10], tempBuffer[MAXSIZE + 1];
	const char * delim = "\r\n";
	ZeroMemory(num, 10);
	ZeroMemory(tempBuffer, MAXSIZE + 1);
	memcpy(tempBuffer, buffer, strlen(buffer));
        p = strtok(tempBuffer, delim); // ��ȡ��һ��
        memcpy(num, &p[9], 3);
        if (strcmp(num, "200") == 0) { // ״̬����200ʱ����
          // printf("url : %s\n", url);
          char filename[100] = {0}; // �����ļ���
          makeFilename(url, filename);
          printf("filename : %s\n", filename);
          FILE *out;
          out = fopen(filename, "w");
          fwrite(buffer, sizeof(char), strlen(buffer), out);
          fclose(out);
          printf("\n=====================================\n\n");
          printf("\n��ҳ�Ѿ�������\n");
        }
}

// ��ȡ����
void getCache(char *buffer, char *filename) {
	char *p, *ptr, num[10], tempBuffer[MAXSIZE + 1];
	const char * delim = "\r\n";
	ZeroMemory(num, 10);
	ZeroMemory(tempBuffer, MAXSIZE + 1);
	memcpy(tempBuffer, buffer, strlen(buffer));
        p = strtok(tempBuffer, delim); // ��ȡ��һ��
        memcpy(num, &p[9], 3);
        if (strcmp(num, "304") ==
            0) { // �������صı����е�״̬��Ϊ304ʱ�����ѻ��������?
          printf("\n=====================================\n\n");
          printf("�ӱ�����û���\n");
          ZeroMemory(buffer, strlen(buffer));
          FILE *in = NULL;
          if ((in = fopen(filename, "r")) != NULL) {
            fread(buffer, sizeof(char), MAXSIZE, in);
            fclose(in);
          }
          needCache = FALSE;
        }
}
