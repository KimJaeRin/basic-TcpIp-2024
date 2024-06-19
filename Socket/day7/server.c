#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>

#define TRUE 1
#define BUF_SIZE 1024

 char webpage[] = "HTTP/1.1 200 OK\r\n"
                   "Server:Linux Web Server\r\n"
                  "Content-Type: text/html; charset=UTF-8\r\n\r\n"
                  "<!DOCTYPE html>\r\n"
                  "<html><head><title> Jaerin's Web Page </title>\r\n"
									"<link rel=\"icon\" href=\"/favicon.ico\">"
                  "<style>body {background-color: #EEE2CC }</style></head>\r\n"
                  "<body><center><h1>Welcome to Jaerin's Web!</h1><br>\r\n"
                   "<img src=\"car.jpg\"></center></body></html>\r\n";

 int main(int argc, char *argv[])
 {
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t sin_len = sizeof(clnt_addr);
    int serv_sock, clnt_sock;
    char buf[2048];
    int fdimg, img_size;
    int option = TRUE;
    char img_buf[500000];

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(argv[1]));
    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) perror("bind() error!!\n");
    if(listen(serv_sock, 5) == -1) perror("listen() error\n");

    while(1)
    {
       clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &sin_len);
       puts("connection...");
       read(clnt_sock, buf, BUF_SIZE);
       printf("%s\n", buf);

       if(strstr(buf, "car.jpg") != NULL)
       {
       		fdimg = open("car.jpg", O_RDONLY);
          if((img_size = read(fdimg, img_buf, sizeof(img_buf))) == -1) puts("file read error!!");
          close(fdimg);
          sprintf(buf, "HTTP/1.1 200 OK\r\n"
           "Server: Linux Web Server\r\n"
           "Content-Type: image/jpeg\r\n"
           "Content-Length: %ld\r\n\r\n", img_size);

       		if(write(clnt_sock, buf, strlen(buf)) < 0) puts("write error");

          if(write(clnt_sock, img_buf, img_size) < 0) puts("write error");

          close(clnt_sock);
       }

       else 
          if(write(clnt_sock, webpage, sizeof(webpage)) == -1) puts("write error!");
       puts("closing");
       close(clnt_sock);
   }
       close(serv_sock);
       return 0;
}
