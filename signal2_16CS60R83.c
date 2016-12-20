#include<stdio.h>
#include<signal.h>
#include<stdlib.h>







void sig_hand(int signal)
{
if(signal==3)
{
printf("SIGINT received\n");
fflush(stdout);
exit(0);
}
if(signal==SIGINT)
{
printf("You pressed Ctrl+C\n");
fflush(stdout);

}

}


int main()
{
struct sigaction sa;
sa.sa_handler=&sig_hand;
sa.sa_flags=SA_SIGINFO;
printf("[%lu]\n",(unsigned long)getpid());
fflush(stdout);
sigaction(SIGINT,&sa,NULL);
sigaction(SIGQUIT,&sa,NULL);
while(1);

}
