
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void read_childproc(int sig){
    
    int status;
    pid_t id=waitpid(-1, &status ,WNOHANG);
    if (WIFEXITED(status)) {
        printf("removed proc id : %d \n" , id);
        printf("child send: %d \n" , WEXITSTATUS(status));
    }
}

int main(int argc, char *argv[])
{
    pid_t pid;
    struct sigaction act;
    act.sa_handler = read_childproc;    //시그널 핸들러는 read_childproc 함수 포인터
    sigemptyset(&act.sa_mask);          //0으로 초기화
    act.sa_flags = 0;                   //0으로 초기화
    sigaction(SIGCHLD, &act , 0);

		pid=fork();
    //자식 프로세스일 경우
    if (pid == 0)
    {
        puts("Hi i am child process");
        sleep(10);
        return 12;
    }
    else {
        //부모 프로세스일 경우
        printf("my child process[1] id : %d \n" , pid);
        pid = fork();
        if (pid == 0) {
		        puts("hi i am child process");
            sleep(10);
            exit(24);
                } else {
                    //부모 프로세스 일경우
                    int i;
                    printf("child  process id : %d \n" , pid);
                    for (i = 0; i < 5; i++) {
                        puts("wait.....");
                        sleep(5);
                    }
                }
    }
	return 0;
}
