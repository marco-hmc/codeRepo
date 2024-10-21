#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#include <cstdlib>

int main() {
    // 生成一个唯一的键
    key_t key = ftok("somefile", 'a');
    if (key == -1) {
        perror("ftok error");
        exit(1);
    }

    // 创建或获取一个消息队列
    int msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget error");
        exit(1);
    }

    struct msgbuf buf;

    // 从消息队列中接收消息
    if (msgrcv(msgid, &buf, sizeof(buf.mtext), 1, 0) == -1) {
        perror("msgrcv error");
        exit(1);
    }

    printf("Received message: %s\n", buf.mtext);

    // 删除消息队列
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl error");
        exit(1);
    }

    return 0;
}