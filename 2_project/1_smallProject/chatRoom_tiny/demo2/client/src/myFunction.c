/*
 * @Author: your name
 * @Date: 2022-02-06 15:59:19
 * @LastEditTime: 2022-02-06 18:31:32
 * @LastEditors: your name
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /chatRoom_tiny/demo2/client/src/myFunction.c
 */
#include "myFunction.h"
#include "myData.h"

void mywrite(int sockfd,vpChat temp)
{
	int num;
    if((num = write(sockfd,temp,sizeof(stChat))) == -1)
    {
        printf("send error!\n");
	}
}