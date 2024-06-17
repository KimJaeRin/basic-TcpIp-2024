#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>



void timeout(int sig){

    if (sig == SIGALRM)
        puts("Time out!");
    alarm(5);
    }

void keycontrol(int sig)
{

    if (sig == SIGINT)
        puts("ctrl + c pressed !");
}

int main(int argc, char *argv[])
{
    int i;
    signal(SIGALRM , timeout);
    signal(SIGINT, keycontrol);
    alarm(2);

    for (i = 0; i < 3; i++) 
    {
        puts("wait...");
        sleep(100);
    }
	return 0;
}
