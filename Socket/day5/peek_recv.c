#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int acpt_sock, recv_sock;
	struct sockaddr_in acpt_adr, recv_adr;
	int str_len, state;
	socklen_t recv_adr_sz;
	char buf[BUF_SIZE];
	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
	acpt_sock=socket(PF_INET, SOCK_STREAM, 0);
	memset(&acpt_adr, 0, sizeof(acpt_adr));
	acpt_adr.sin_family=AF_INET;
	acpt_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	acpt_adr.sin_port=htons(atoi(argv[1]));
	
  	if(bind(acpt_sock, (struct sockaddr*)&acpt_adr, sizeof(acpt_adr))==-1)
		error_handling("bind() error");
	listen(acpt_sock, 5);
	
	recv_adr_sz=sizeof(recv_adr);
	recv_sock=accept(acpt_sock, (struct sockaddr*)&recv_adr, &recv_adr_sz);
	
	while(1)
	{
		str_len=recv(recv_sock, buf, sizeof(buf)-1, MSG_PEEK|MSG_DONTWAIT); //MSG_PEEK와 MSG_DONTWAIT를 옵션으로 넣음.        
		if(str_len>0) //MSG_PEEK : 입력 버퍼에 데이터 유무 확인하고 입력버퍼의 데이터를 지우지 않고 유지함. , MSG_DONTWAIT : 데이터가 없어도 블로킹 상태에 놓이지 않게 함.
			break;
	}

	buf[str_len]=0;
	printf("Buffering %d bytes: %s \n", str_len, buf);
 	
	str_len=recv(recv_sock, buf, sizeof(buf)-1, 0); //데이터를 읽은 뒤 입력버퍼의 데이터를 지운다.
	buf[str_len]=0;
	printf("Read again: %s \n", buf);
	close(acpt_sock);
	close(recv_sock);
	return 0; 
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
 
