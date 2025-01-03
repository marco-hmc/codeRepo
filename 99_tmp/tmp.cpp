#include <iostream>

void dsend(int count) {
    int n;
    if (!count) return;   // 如果 count 为 0，直接返回
    n = (count + 7) / 8;  // 计算需要执行的循环次数
    switch (count % 8) {  // 根据 count % 8 的值选择起始 case
        case 0:
            do {
                puts("case 0");
                case 7:
                    puts("case 7");
                case 6:
                    puts("case 6");
                case 5:
                    puts("case 5");
                case 4:
                    puts("case 4");
                case 3:
                    puts("case 3");
                case 2:
                    puts("case 2");
                case 1:
                    puts("case 1");
            } while (--n > 0);  // 循环执行，直到 n 减少到 0
    }
}

int main() {
    dsend(10);  // 示例调用
    return 0;
}