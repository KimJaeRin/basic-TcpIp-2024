#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	FILE * readfp;
	FILE * writefp;
	
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;
	char buf[BUF_SIZE]={0,};

	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));
	
	bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr));
	listen(serv_sock, 5);
	clnt_adr_sz=sizeof(clnt_adr); 
	clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr,&clnt_adr_sz);
	
	readfp=fdopen(clnt_sock, "r");
	writefp=fdopen(dup(clnt_sock), "w"); //dup 기능을 이용해서 clnt_sock 파일디스크립터를 복사했다.
	
	fputs("FROM SERVER: Hi~ client? \n", writefp);
	fputs("I love all of the world \n", writefp);
	fputs("You are awesome! \n", writefp);
	fflush(writefp);
	
	shutdown(fileno(writefp), SHUT_WR); //shutdown을 이용해서 writefp로 EOF 신호를 보냈다. 
	fclose(writefp);
	
	fgets(buf, sizeof(buf), readfp); fputs(buf, stdout); //writefp는 닫혔어도, readfp는 살아있음을 알 수 있다.
	fclose(readfp);
	return 0;
}
