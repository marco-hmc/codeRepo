/*
 * @Author: your name
 * @Date: 2021-12-10 14:58:16
 * @LastEditTime: 2022-02-05 19:33:15
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /mySocket/02demo/hello_client.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char *argv[]){
    int clnt_socket;
    char msg[1024];
    int str_len;
    struct sockaddr_in serv_addr;

    if (argc != 3){
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    clnt_socket = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    connect(clnt_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    fputs("Input Q to exit\n", stdout);
    fputs("echoing system start, plz input your msg\n", stdout);
    while(1){    
        fgets(msg, sizeof(msg), stdin);
        if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n")) // 等于则返回0
            break;
        write(clnt_socket, msg, strlen(msg)); 
        str_len = read(clnt_socket, msg, sizeof(msg) - 1);
        printf("str_len: %d, msg: %s\n", str_len, msg);
        msg[str_len] = 0;
        printf("msg from server: %s\n", msg);
    }
    close(clnt_socket);
    return 0;
}