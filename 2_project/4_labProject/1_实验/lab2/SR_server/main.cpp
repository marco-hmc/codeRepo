//#include "stdafx.h" //���� VS ��Ŀ������Ԥ����ͷ�ļ�
#include <stdlib.h>
#include <time.h>
#include <WinSock2.h>
#include <fstream>

#pragma comment(lib,"ws2_32.lib")

#define SERVER_PORT  12340  //�˿ں�
#define SERVER_IP  "0.0.0.0" //IP ��ַ
const int BUFFER_LENGTH = 1026; //��������С�� ����̫���� UDP ������֡�а�����ӦС�� 1480 �ֽڣ�
const int SEND_WIND_SIZE = 10;//���ʹ��ڴ�СΪ 10��GBN ��Ӧ���� W + 1 <=N��W Ϊ���ʹ��ڴ�С��N Ϊ���кŸ�����

//����ȡ���к� 0...19 �� 20 ��
//��������ڴ�С��Ϊ 1����Ϊͣ-��Э��
const int SEQ_SIZE = 20; //���кŵĸ������� 0~19 ���� 20 ��
const int SEQ_NUMBER = 9;

//���ڷ������ݵ�һ���ֽ����ֵΪ 0�� �����ݻᷢ��ʧ��
//��˽��ն����к�Ϊ 1~20���뷢�Ͷ�һһ��Ӧ
BOOL ack[SEQ_SIZE];//�յ� ack �������Ӧ 0~19 �� ack
char dataBuffer[SEQ_SIZE][BUFFER_LENGTH];
int curSeq;      //��ǰ���ݰ��� seq
int curAck;      //��ǰ�ȴ�ȷ�ϵ� ack
int totalPacket; //��Ҫ���͵İ�����

int totalSeq;     //�ѷ��͵İ�������
int totalAck;     //ȷ���յ���ack���İ�������
int finish;       //��־λ�����ݴ����Ƿ���ɣ�finish=1->���ݴ�������ɣ�
int finish_S;

//************************************
// Method: getCurTime
// FullName: getCurTime
// Access: public
// Returns: void
// Qualifier: ��ȡ��ǰϵͳʱ�䣬������� ptime ��
// Parameter: char * ptime
//************************************
void getCurTime(char *ptime){
	char buffer[128];
	memset(buffer,0,sizeof(buffer));
	time_t c_time;
	struct tm *p;
	time(&c_time);
	p = localtime(&c_time);
	sprintf(buffer,"%d/%d/%d %d:%d:%d",
	p->tm_year + 1900,
	p->tm_mon + 1,
	p->tm_mday,
	p->tm_hour,
	p->tm_min,
	p->tm_sec);
	strcpy(ptime,buffer);
}

//************************************
// Method: seqIsAvailable
// FullName: seqIsAvailable
// Access: public
// Returns: bool
// Qualifier: ��ǰ���к� curSeq �Ƿ����
//************************************
int seqIsAvailable(){
	int step;
	step = curSeq - curAck;
	step = step >= 0 ? step : step + SEQ_SIZE;
	//���к��Ƿ��ڵ�ǰ���ʹ���֮��
	if(step >= SEND_WIND_SIZE){
		return 0;
	}
	if(!ack[curSeq]){//ack[curSeq]==FALSE
		return 1;
	}
	return 2;
}

//************************************
// Method: timeoutHandler
// FullName: timeoutHandler
// Access: public
// Returns: void
// Qualifier: ��ʱ�ش���������
//************************************
void timeoutHandler(){
	printf("Timer out error.");
	int index;

	/*Ϊ�ж����ݴ����Ƿ������ӻ��޸ĵ����*/
	if(totalSeq==totalPacket){//֮ǰ���͵������һ�����ݰ�
		if(curSeq>curAck){
			totalSeq -= (curSeq-curAck);
		}
		else if(curSeq<curAck){
			totalSeq -= (curSeq-curAck+20);
		}
	}
	else{//֮ǰû���͵����һ�����ݰ�
		totalSeq -= SEND_WIND_SIZE;
	}
	/*Ϊ�ж����ݴ����Ƿ������ӻ��޸ĵ����*/

	curSeq = curAck;
}

//************************************
// Method: ackHandler
// FullName: ackHandler
// Access: public
// Returns: void
// Qualifier: �յ� ack���ۻ�ȷ�ϣ�ȡ����֡�ĵ�һ���ֽ�
//���ڷ�������ʱ����һ���ֽڣ����кţ�Ϊ 0��ASCII��ʱ����ʧ�ܣ���˼�һ�ˣ��˴���Ҫ��һ��ԭ
// Parameter: char c
//************************************
void ackHandler(char c){
	unsigned char index = (unsigned char)c - 1;    //���кż�һ
	printf("Recv a ack of seq %d \n",index + 1);   //�ӽ��շ��յ���ȷ���յ������к�
	int all;
	int next;
	int add;
	all = 1;

	if(curAck == index){
		add = 1;
		totalAck += 1;
		ack[index] = FALSE;
		curAck = (index + 1) % SEQ_SIZE;
		for(int i = 1;i<SEQ_SIZE;i++){
			next=(i+index)%SEQ_SIZE;
			if(ack[next]==TRUE){
				ack[next]=FALSE;
				curAck = (next + 1) % SEQ_SIZE;
				totalSeq++;
				++curSeq;
				curSeq %= SEQ_SIZE;
			}
			else{
				break;
			}
		}
		printf("\t\tcurAck == index , totalAck += %d\n",add);
	}
	else if(curAck < index && index-curAck + 1 <= SEND_WIND_SIZE){//Ҫ��֤��Ҫ���ܵ���Ϣ���ڻ��������ڣ�
		if(!ack[index]){
			printf("\t\tcurAck < index , totalAck += %d\n",1);
			totalAck += 1;
			ack[index] = TRUE;
		}
	}else if(SEQ_SIZE - curAck + index + 1 <= SEND_WIND_SIZE && curAck > index){ //Ҫ��֤��Ҫ���ܵ���Ϣ���ڻ��������ڣ�
		if(!ack[index]){
			printf("\t\tcurAck > index , totalAck += %d\n",1);
			totalAck += 1;
			ack[index] = TRUE;
		}

	}
}

//************************************
// Method: lossInLossRatio
// FullName: lossInLossRatio
// Access: public
// Returns: BOOL
// Qualifier: ���ݶ�ʧ���������һ�����֣��ж��Ƿ�ʧ,��ʧ�򷵻� TRUE�����򷵻� FALSE
// Parameter: float lossRatio [0,1]
//************************************
BOOL lossInLossRatio(float lossRatio) {
	int lossBound = (int) (lossRatio * 100);
	int r = rand() % 101;
	if(r <= lossBound){
		return TRUE;
	}
	return FALSE;
}

//************************************
// Method: seqRecvAvailable
// FullName: seqRecvAvailable
// Access: public
// Returns: bool
// Qualifier: ��ǰ�յ������к� recvSeq �Ƿ��ڿ��շ�Χ��
//************************************
BOOL seqRecvAvailable(int recvSeq) {
	int step;
	int index;
	index = recvSeq - 1;
	step = index - curAck;
	step = step >= 0 ? step : step + SEQ_SIZE;
	//���к��Ƿ��ڵ�ǰ���ʹ���֮��
	if(step >= SEND_WIND_SIZE){
		return FALSE;
	}
	return TRUE;
}

//������
int main(int argc, char* argv[])
{
	//�����׽��ֿ⣨���룩
	WORD wVersionRequested;
	WSADATA wsaData;
	//�׽��ּ���ʱ������ʾ
	int err;
	//�汾 2.2
	wVersionRequested = MAKEWORD(2, 2);
	//���� dll �ļ� Scoket ��
	err = WSAStartup(wVersionRequested, &wsaData);
	if(err != 0){
		//�Ҳ��� winsock.dll
		printf("WSAStartup failed with error: %d\n", err);
		return -1;
	}
	if(LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) !=2)
	{
		printf("Could not find a usable version of Winsock.dll\n");
		WSACleanup();
	}else{
		printf("The Winsock 2.2 dll was found okay\n");
	}
	SOCKET sockServer = socket(AF_INET, SOCK_DGRAM,IPPROTO_UDP);
	//�����׽���Ϊ������ģʽ
	int iMode = 1; //1����������0������
	ioctlsocket(sockServer,FIONBIO, (u_long FAR*) &iMode);//����������
	SOCKADDR_IN addrServer; //��������ַ
	//addrServer.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);
	addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//���߾���
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(SERVER_PORT);
	err = bind(sockServer,(SOCKADDR*)&addrServer, sizeof(SOCKADDR));
	if(err){
		err = GetLastError();
		printf("Could  not  bind  the  port  %d  for  socket.Error  code   is %d\n",SERVER_PORT,err);
		WSACleanup();
		return -1;
	}
	float packetLossRatio = 0.2;    //Ĭ�ϰ���ʧ�� 0.2
	float ackLossRatio = 0.2;       //Ĭ�� ACK ��ʧ�� 0.2
	//��ʱ����Ϊ������ӣ�����ѭ����������
	srand((unsigned)time(NULL));
	SOCKADDR_IN addrClient;         //�ͻ��˵�ַ
	int length = sizeof(SOCKADDR);
	char buffer[BUFFER_LENGTH];     //���ݷ��ͽ��ջ�����
	ZeroMemory(buffer,sizeof(buffer));
	//���������ݶ����ڴ�
	std::ifstream icin;
	icin.open("test.txt");
	char data[1024 * SEQ_NUMBER];
	ZeroMemory(data,sizeof(data));
	icin.read(data,1024 * SEQ_NUMBER);
	icin.close();
	totalPacket = sizeof(data) / 1024;
	printf("totalPacket is ��%d\n\n",totalPacket);
	int recvSize ;
	finish = 0;
	finish_S = 0;
	for(int i=0; i < SEQ_SIZE; ++i){
		ack[i] = FALSE;
	}
	while(true){
		//���������գ���û���յ����ݣ�����ֵΪ-1
		recvSize  = recvfrom(sockServer,buffer,BUFFER_LENGTH,0,((SOCKADDR*)&addrClient),&length);
		if(recvSize < 0){
			Sleep(200);
			continue;
		}
		printf("recv from client: %s\n",buffer);
		if(strcmp(buffer,"-time") == 0){
            printf("�յ� -time");
			getCurTime(buffer);
		}else if(strcmp(buffer,"-quit") == 0){
			strcpy(buffer,"Good bye!");
		}else if(strcmp(buffer,"-testsr") == 0){
			//���� gbn ���Խ׶�
			//���� server��server ���� 0 ״̬���� client ���� 205 ״̬�루server���� 1 ״̬��
			//server �ȴ� client �ظ� 200 ״̬�룬 ����յ� ��server ���� 2 ״̬�� ����ʼ�����ļ���������ʱ�ȴ�ֱ����ʱ\
			//���ļ�����׶Σ�server ���ʹ��ڴ�С��Ϊ
			for(int i=0; i < SEQ_SIZE; ++i){
				ack[i] = FALSE;
			}
			ZeroMemory(buffer,sizeof(buffer));
			int recvSize;
			int waitCount = 0;
			finish=0;
			printf("Begain to test SR protocol,please don't abort the process\n");
			//������һ�����ֽ׶�
			//���ȷ�������ͻ��˷���һ�� 205 ��С��״̬�루���Լ�����ģ���ʾ������׼�����ˣ����Է�������
			//�ͻ����յ� 205 ֮��ظ�һ�� 200 ��С��״̬�룬��ʾ�ͻ��˱����ˣ����Խ���������
			//�������յ� 200 ״̬��֮�󣬾Ϳ�ʼʹ�� GBN ����������
			printf("Shake hands stage\n");
			int stage = 0;
			bool runFlag = true;
			while(runFlag){
				switch(stage){
					case 0://���� 205 �׶�
						buffer[0] = 205;
						sendto(sockServer,  buffer,  strlen(buffer)+1,  0,
						(SOCKADDR*)&addrClient, sizeof(SOCKADDR));
						Sleep(100);
						stage = 1;
						break;
					case 1://�ȴ����� 200 �׶Σ�û���յ��������+1����ʱ������˴Ρ����ӡ����ȴ��ӵ�һ����ʼ
						recvSize  =  recvfrom(sockServer,buffer,BUFFER_LENGTH,0,((SOCKADDR*)&addrClient),&length);
						if(recvSize < 0){
							++waitCount;
							if(waitCount > 20){
								runFlag = false;
								printf("Timeout error\n");
								break;
							}
							Sleep(500);
							continue;
						}else{
							if((unsigned char)buffer[0] == 200){
								printf("Begin a file transfer\n");
								printf("File size is %dB, each packet is 1024B  and packet total num is %d\n",sizeof(data),totalPacket);
								curSeq = 0;
								curAck = 0;
								totalSeq = 0;
								waitCount = 0;
								totalAck=0;
								finish=0;
								stage = 2;
							}
						}
						break;
					case 2://���ݴ���׶�

						/*�ж����ݴ����Ƿ������ӻ��޸�*/
						if(seqIsAvailable()==1 && totalSeq<=(totalPacket-1)){//totalSeq<=(totalPacket-1)��δ�������һ�����ݰ�

							//���͸��ͻ��˵����кŴ� 1 ��ʼ
							buffer[0] = curSeq + 1;
							ack[curSeq] = FALSE;
							//���ݷ��͵Ĺ�����Ӧ���ж��Ƿ������->���ڴ˴����Ѿ�ʵ����ok
							//Ϊ�򻯹��̴˴���δʵ��->���ڴ˴����Ѿ�ʵ����ok
							memcpy(&buffer[1],data + 1024 * totalSeq,1024);
							printf("send a packet with a seq of : %d \t totalSeq now is : %d\n",curSeq+1,totalSeq+1);
							sendto(sockServer, buffer, BUFFER_LENGTH, 0,
							(SOCKADDR*)&addrClient, sizeof(SOCKADDR));
							++curSeq;
							curSeq %= SEQ_SIZE;
							++totalSeq;
							Sleep(500);
						}
						else if(seqIsAvailable()==2 && totalSeq<=(totalPacket-1)){
							++curSeq;
							curSeq %= SEQ_SIZE;
							++totalSeq;
							//Sleep(500);
							printf("\t\tBREAK1!\n");
							break;
							//printf("\t\tBREAK2!\n");
						}
						//�ȴ� Ack����û���յ����򷵻�ֵΪ-1��������+1
						recvSize  =  recvfrom(sockServer,buffer,BUFFER_LENGTH,0,((SOCKADDR*)&addrClient),&length);
						if(recvSize < 0){
							waitCount++;
							//20 �εȴ� ack ��ʱ�ش�
							if (waitCount > 20)
							{
								timeoutHandler();
								printf("\t----totalSeq Now is : %d\n",totalSeq);
								waitCount = 0;
							}
							}else{
							//�յ� ack
							ackHandler(buffer[0]);
							printf("\t\t----totalAck Now is : %d\n",totalAck);
							waitCount = 0;


							/*Ϊ�ж����ݴ����Ƿ������ӻ��޸ĵ����*/
							if(totalAck==totalPacket){//���ݴ������
								finish=1;
								break;
							}
							/*Ϊ�ж����ݴ����Ƿ������ӻ��޸ĵ����*/
						}
						Sleep(500);
						break;
				}


				/*Ϊ�ж����ݴ����Ƿ������ӻ��޸ĵ����*/
				if(finish==1){
					printf("���ݴ���ȫ����ɣ�����\n");
					strcpy(buffer,"���ݴ���ȫ����ɣ�����\n");
					sendto(sockServer, buffer, strlen(buffer)+1, 0, (SOCKADDR*)&addrClient,sizeof(SOCKADDR));
					break;
				}
				/*Ϊ�ж����ݴ����Ƿ������ӻ��޸ĵ����*/
			}
		}
		else if(strcmp(buffer,"-testsr_Send") == 0){
			iMode = 0; //1����������0������
			ioctlsocket(sockServer,FIONBIO, (u_long FAR*) &iMode);//����������
			printf("%s\n","Begin to test GBN protocol, please don't abort the  process");
			printf("The loss ratio of packet is %.2f,the loss ratio of ack  is %.2f\n",packetLossRatio,ackLossRatio);
			int waitCount = 0;
			int stage = 0;
			finish_S=0;
			BOOL b;
			curAck=0;
			for(int i=0; i < SEQ_SIZE; ++i){
				ack[i] = FALSE;
			}
			unsigned char u_code;//״̬��
			unsigned short seq;//�������к�
			unsigned short recvSeq;//���մ��ڴ�СΪ 1����ȷ�ϵ����к�
			unsigned short waitSeq;//�ȴ������к�
			int next;
			sendto(sockServer,  "-testsr_Send",  strlen("-testsr_Send")+1,  0,
			(SOCKADDR*)&addrClient, sizeof(SOCKADDR));
			while (true)
			{
				//�ȴ� server �ظ����� UDP Ϊ����ģʽ
				recvfrom(sockServer,buffer,BUFFER_LENGTH,0,(SOCKADDR*)&addrClient, &length);

				/*�ж����ݴ����Ƿ������ӻ��޸�*/
				if(!strcmp(buffer,"���ݴ���ȫ����ɣ�����\n")){
					finish_S=1;
					break;
				}
				/*�ж����ݴ����Ƿ������ӻ��޸�*/

				switch(stage){
					case 0://�ȴ����ֽ׶�
						u_code = (unsigned char)buffer[0];
						if ((unsigned char)buffer[0] == 205)
						{
							printf("Ready for file transmission\n");
							buffer[0] = 200;
							buffer[1] = '\0';
							sendto(sockServer,  buffer,  2,  0, (SOCKADDR*)&addrClient, sizeof(SOCKADDR));
							stage = 1;
							recvSeq = 0;
							waitSeq = 1;
						}
						break;
					case 1://�ȴ��������ݽ׶�
						seq = (unsigned short)buffer[0];
						//�����ģ����Ƿ�ʧ
						b = lossInLossRatio(packetLossRatio);
						if(b){
							printf("The packet with a seq of %d loss\n",seq);
							continue;
						}
						printf("recv a packet with a seq of %d\n",seq);
						//������ڴ��İ�����ȷ���գ�����ȷ�ϼ���
						if(seqRecvAvailable(seq)){
							recvSeq = seq;
							ack[seq-1]=TRUE;
							ZeroMemory(dataBuffer[seq-1],sizeof(dataBuffer[seq-1]));
							strcpy(dataBuffer[seq-1],&buffer[1]);
							buffer[0] = recvSeq;
							buffer[1] = '\0';
							int tempt=curAck;
							if(seq-1==curAck){
								for(int i=0;i<SEQ_SIZE;i++){
									//printf("\t\ti=%d",i);
									next=(tempt+i)%SEQ_SIZE;
									if(ack[next]){
										//�������
										//printf("\t\ti=%d",i);
										printf("\n\n\t\tACK SEQ: %d\n%s\n\n",(next+1)%SEQ_SIZE,dataBuffer[next]);
										curAck=(next+1)%SEQ_SIZE;
										ack[next]=FALSE;
									}
									else{
										break;
									}
								}
							}

						}
						else{
							recvSeq = seq;
							buffer[0] = recvSeq;
							buffer[1] = '\0';
						}

						b = lossInLossRatio(ackLossRatio);
						if(b){
							printf("The  ack  of  %d  loss\n",(unsigned char)buffer[0]);
							continue;
						}
						sendto(sockServer,  buffer,  2,  0, (SOCKADDR*)&addrClient, sizeof(SOCKADDR));
						printf("send a ack of %d\n",(unsigned char)buffer[0]);
						break;
				}
				Sleep(500);
			}
			iMode = 1; //1����������0������
			ioctlsocket(sockServer,FIONBIO, (u_long FAR*) &iMode);//����������
		}
		if(finish_S==1){
			printf("���ݴ���ȫ����ɣ�����\n\n");
			finish_S=0;
			continue;
		}
		if(finish==1){
			finish=0;
			continue;
		}
		sendto(sockServer, buffer, strlen(buffer)+1, 0, (SOCKADDR*)&addrClient,sizeof(SOCKADDR));
		Sleep(500);
	}
	//�ر��׽��֣�ж�ؿ�
	closesocket(sockServer);
	WSACleanup();
	return 0;
}
