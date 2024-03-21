/*
 * @Author: your name
 * @Date: 2021-12-10 14:57:59
 * @LastEditTime: 2022-02-05 19:33:26
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /mySocket/02demo/hello_server.c
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char *argv[]){
    int serv_socket, clnt_socket;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;
    char msg[1024];
    int str_len, i;

    if (argc!=2){
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    serv_socket = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    bind(serv_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(serv_socket, 5);

    clnt_addr_size = sizeof(clnt_addr);
    for(int i = 0; i < 5; i++){
        clnt_socket = accept(serv_socket, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
        while((str_len = read(clnt_socket, msg, 1024))!=0)
            write(clnt_socket, msg, str_len);
        close(clnt_socket);
    }
    close(serv_socket);
    return 0;
}