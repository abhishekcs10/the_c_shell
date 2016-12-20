#include<signal.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>

void signal_handler(int signal)
{

printf("SIGUSR1 received\n");


}

int main()
{

struct sigaction handle_sig;
handle_sig.sa_handler = &signal_handler;
handle_sig.sa_flags=SA_SIGINFO;
printf("[%lu]\n",(unsigned long)getpid());
sigaction(SIGUSR1, &handle_sig,NULL);
while(1);

}
