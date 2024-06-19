#include <stdio.h>
#include <stdlib.h>	
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUF_SIZE 256	
#define MAX_CLNT 256	

void * handle_clnt(void * arg);
void send_msg(char * msg, int len);
void error_handling(char * msg);

int clnt_cnt=0;
int clnt_socks[MAX_CLNT];
pthread_mutex_t mutx;

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;		// 소켓 통신용 서버 소켓과 임시 클라이언트 소켓
	struct sockaddr_in serv_adr, clnt_adr;	// 서버 주소, 클라이언트 주소 구조체
	int clnt_adr_sz;			// 클라이언트 주소 구조체
	pthread_t t_id;			// 클라이언트 쓰레드용 ID
	// 포트 입력 안했으면
	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);	// 사용법을 알려준다.
		exit(1);						// 프로그램 비정상 종료
	}

	pthread_mutex_init(&mutx, NULL);	// 커널에서 Mutex 쓰기위해 얻어 온다.
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);	// TCP용 소켓 생성
	memset(&serv_adr, 0, sizeof(serv_adr));	// 서버 주소 구조체 초기화
	serv_adr.sin_family=AF_INET; 		// 인터넷 통신
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);	// 현재 IP를 이용하고
	serv_adr.sin_port=htons(atoi(argv[1])); // 포트는 사용자가 지정한 포트 사용

	if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");

	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");

	while(1)	// 무한루프 
	{
		clnt_adr_sz=sizeof(clnt_adr);
  	clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
		pthread_mutex_lock(&mutx);		
		clnt_socks[clnt_cnt++]=clnt_sock;
		pthread_mutex_unlock(&mutx);
		pthread_create(&t_id, NULL, handle_clnt, (void*)&clnt_sock);	// 쓰레드 시작
		pthread_detach(t_id);
		printf("Connected client IP: %s \n", inet_ntoa(clnt_adr.sin_addr));
	}
	close(serv_sock);	// 쓰레드가 끝나면 소켓을 닫아준다.

	return 0;

}

void * handle_clnt(void * arg)
{
	int clnt_sock=*((int*)arg);
	int str_len=0, i;
	char msg[BUF_SIZE];

	while((str_len=read(clnt_sock, msg, sizeof(msg)))!=0)
		send_msg(msg, str_len);

	pthread_mutex_lock(&mutx);// 임계 영역 시작
	for(i=0; i<clnt_cnt; i++)
	{
		if(clnt_sock==clnt_socks[i])
		{
			while(i++<clnt_cnt-1)
				clnt_socks[i]=clnt_socks[i+1];
			break;
		}
	}
	clnt_cnt--;
	pthread_mutex_unlock(&mutx); // 임계 영역 끝
	close(clnt_sock);
	return NULL;
}

void send_msg(char * msg, int len)
{
	int i;
	pthread_mutex_lock(&mutx);
	for(i=0; i<clnt_cnt; i++)
		write(clnt_socks[i], msg, len);

	pthread_mutex_unlock(&mutx);
}

void error_handling(char * msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}
