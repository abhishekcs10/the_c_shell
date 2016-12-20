#include<stdio.h>
#include<signal.h>
#include<stdlib.h>


void sig_hand2(int sign)
{
	printf("I am taking rest now\n");
	fflush(stdout);

	signal(SIGINT,SIG_DFL);

}



void sig_hand(int signal)
{
	struct sigaction sa;
	sa.sa_handler=&sig_hand2;
	sa.sa_flags=SA_SIGINFO;

	FILE *fp=fopen("temp","w+");
	fputs("INTERRUPT",fp);
	fflush(fp);

	sigaction(SIGINT,&sa,NULL);

}


int main()
{
	struct sigaction sa;
	sa.sa_handler=&sig_hand;
	sa.sa_flags=SA_SIGINFO;
	printf("[%lu]\n",(unsigned long)getpid());
	fflush(stdout);
	sigaction(SIGINT,&sa,NULL);
	while(1);

}



