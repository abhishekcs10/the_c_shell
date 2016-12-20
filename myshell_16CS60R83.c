/*
Author: Abhishek Tiwari
file:myshell_16CS60R83

*/



#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<signal.h>
#include<errno.h>
#include<termios.h>
#define COMMAND_LEN 100
#define COM_ARG 100
#define STR_DIR_LEN 256


/*this funtion was to allocate memory for getline function
now obsolete*/
void get_mem(char *str,int num_char)
{
	str=(char *)malloc(sizeof(char)*(num_char+2));
	if(str==NULL)
		printf("error\n");

}


/*
This function behaves like function getch in turbo c compiler
uses termios.h header file to turn ECHO mode on or off for the terminal using the tsetattr structure


referred from stackoverflow

*/
int getch(void)
{
	int ch;
	struct termios oldt, newt;

	tcgetattr ( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr ( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr ( STDIN_FILENO, TCSANOW, &oldt );

	return ch;

}

/*
Every child sends a SIGCHLD signal to parent when it terminates. This funtion acknowledges those SIGCHLD signals .
The effect of not using this signal handler was that even if process finishes its task it was not removed from the ps list of processes


*/
void signal_handler(int sig)
{
	pid_t pid;
	int saved_errno = errno;  //this errno is from errno.h to check for error code from child

	while (1) 
	{
		pid=waitpid((pid_t)(-1), 0, WNOHANG); 
		if (pid == 0)
			return;
		else if (pid == -1)
			return;
		else
			printf ("%d Exited\n", pid);
	}
	errno = saved_errno;
	//	if(pid>0)
	//	printf("%d process exited\n",pid);
	fflush(stdout);


}

//no use
/*void save_history(char *argv)
  {
  FILE *fp;
  char *str;
  size_t allo;
  ssize_t done;
  char *history;
  history=(char *)malloc(sizeof(char)*2056);
  history=getenv("HOME");
  strcat(history,"/.history");
  fp=fopen(history,"a");
  if(fp==NULL)
  printf("Error");
  int size=ftell(fp);
  if(size!=0)
  fprintf(fp,"%s","\n");
  fprintf(fp,"%s",argv);

  fclose(fp);
  return;
  }
 */
/*

This funtion executes the the command stored in cmd (a 2D array)
and num_param is the number of arguements in 2D array

*/

void do_execute(char **cmd,int num_param)
{
	pid_t child_proc,stat;
	int cstatus,iter_file,len_file=strlen(*cmd),background=0;
	char *cmd_file;
	static pid_t child_process[1024],check_fin[1024];
	static int child_no=-1,status[1024];
	struct sigaction sa;         //the sigaction is used to control signals or send signals to child process
	sa.sa_handler=&signal_handler;	//registering the signal handler funtion i.e providing the functional pointer
	sigemptyset(&sa.sa_mask);
	sa.sa_flags=SA_RESTART|SA_NOCLDSTOP;//reffered from stackoverflow
	if(sigaction(SIGCHLD,&sa,0)==-1){	//starting the function 

		perror(0);
		exit(1);
	}
	cmd_file=(char *)malloc(sizeof(char)*STR_DIR_LEN+len_file+4);
//handling for mycd command and setting pwd environment variable
	if((strcmp(*cmd,"mycd")==0)||strcmp(*cmd,"cd")==0)
	{if(chdir(cmd[1]))
		printf("Error\n");
		else{
			char *command,*exec;
			command=(char *)malloc(sizeof(char)*10004);
			exec=(char *)malloc(sizeof(char)*10004);
			getcwd(command,sizeof(char)*10004);
			if((setenv("PWD",command,1))!=0)
				printf("Error changing directory\n");
		}
		return;
	}
	//   strcpy(cmd_file,abs_path);
	//  strcat(cmd_file,*cmd);

//forking process to start child
	if ((child_proc=fork())==0)
	{
		//child
		if(strcmp(cmd[num_param-1],"&")==0)
		{   //detaching launched process from current terminal
			cmd[num_param-1]=NULL;
			 setpgid(0,0);  
			//	background=1;

		}
else if(cmd[num_param-1][strlen(cmd[num_param-1])-1]=='&')
{
cmd[num_param-1][strlen(cmd[num_param-1])-1]='\0';
setpgid(0,0);
}
		execvp(cmd[0],cmd);
		fprintf(stderr,"command not executed\n");
		exit(1);
	}
	else{

		if(child_proc<(pid_t)0)
			printf("error creating child");
		else
		{
			//parent
			if((strcmp(cmd[num_param-1],"&")==0)||(cmd[num_param-1][strlen(cmd[num_param-1])-1])=='&')
				background=1;
			
			if(background)
			{
				printf("%d\n",child_proc);
				child_process[++child_no]=child_proc;	
			}
			
			else
				waitpid(child_proc,&cstatus,WIFEXITED(&cstatus));

		}

	     }


	}









	int main()
	{
		char *shell_command,user[256],*token,*param[COM_ARG],*exec_cmd,*cmd_file,*get_path,*display_dir,key,printf_stat[2056],get_hist[2056],*print_hist,*current_command,*history_file,*temp_history;
		pid_t his_child;
		FILE *fp;
		size_t len_read;
		size_t len_cmd=COMMAND_LEN;
		int num_param,iter_file,inp_iter,cursor=0,hstatus,history_count=0,show_current,zid=0,current_cursor=0;
		cmd_file=(char *)malloc(sizeof(char)*STR_DIR_LEN+1);
		history_file=(char *)malloc(sizeof(char)*2056);
		temp_history=(char *)malloc(sizeof(char)*2056);
		print_hist=(char *)malloc(sizeof(char)*2056);
		getcwd(cmd_file,STR_DIR_LEN+1); // get current directory where all your files are stored 
		setenv("PWD",cmd_file,1);//set current working directory variable
		get_path=getenv("PATH");//get path variable for current shell
		history_file=getenv("HOME");
		char *pipe_file=(char *)malloc(sizeof(char)*1024);
		pipe_file=getenv("HOME");
		setenv("HOME",history_file,1);
		
		strcpy(temp_history,history_file);
		strcat(history_file,"/.history");
		strcat(temp_history,"/.getline");
		fp=fopen(history_file,"w");
		fclose(fp);	
		//		system("rm ~/.history");

		if(get_path==NULL)
		{
			printf("Error\n");
		}
		strcat(get_path,":");// path format => PATH:your_path
		strcat(get_path,cmd_file);
		setenv("PATH",get_path,1);

		printf("Login User Name\n");
		gets(user);
		printf("Logging in...\n");
		while(1)
		{   
			display_dir=getenv("PWD");
			if(display_dir==NULL)
				printf("Error chaging directory\n");
			sprintf(printf_stat,"[%s@google:%s]$ ",user,display_dir);
			printf("%s",printf_stat);
			//read command entered on shell

			shell_command=(char *)malloc(sizeof(char)*(len_cmd+1));
			shell_command[0]='\0';
			//		len_read = getline (&shell_command, &len_cmd, stdin);
			inp_iter=0,cursor=strlen(printf_stat);
			len_read=cursor;
			show_current=history_count+1;
			current_command=(char *)malloc(sizeof(char)*2056);
			current_command[0]='\0';
			int last_com_len,current_com_len=0;
//handling of keys to detect up and down motion	
system("rm .out 2> /dev/null");
		while((key=getch())!='\n')
			{
				if(key=='\033')
				{
					//printf("here");
					key=getch();
					switch(getch()){
						case 'A':
							{
								//printf("up\n");
								if(show_current==1)
									break;
								show_current--;
								printf("\33[2K\r");
								printf("%s",printf_stat);
								sprintf(get_hist,"sed \"%dq;d\" %s>%s",show_current,history_file,temp_history);
								//printf("a");
								system(get_hist);

								fp=fopen(temp_history,"r");
								getline(&print_hist,&len_read,fp);
								fclose(fp);
								if(print_hist[strlen(print_hist)-1]=='\n')
									print_hist[strlen(print_hist)-1]='\0';
								current_cursor=len_read+strlen(print_hist);						
								printf("%s",print_hist);
								fflush(stdout);
								last_com_len=strlen(print_hist);
								strcpy(current_command,print_hist);
								current_com_len=last_com_len;		
								cursor=(int)(strlen(printf_stat))+last_com_len;
								break;
							}
						case 'B':
							{
								show_current++;
								printf("\33[2K\r");
								printf("%s",printf_stat);
								if(show_current==history_count+1)
								{
									*(shell_command+inp_iter)='\0';
									printf("%s",shell_command);
									strcpy(current_command,shell_command);
									current_cursor=(int)strlen(printf_stat)+strlen(shell_command);
								}
								//show_current++;				//show_current stores current position of pointer on some nth line in file 
								else if(show_current>history_count+1)		//history_count stores total number of history entries
									break;
								else
								{

									sprintf(get_hist,"sed \"%dq;d\" %s>%s",show_current,history_file,temp_history);
									system(get_hist);
									fp=fopen(temp_history,"r");
									if(fp==NULL)
										break;
									else
									{
										getline(&print_hist,&len_read,fp);
										fclose(fp);
										print_hist[strlen(print_hist)-1]='\0';
										printf("%s",print_hist);
										current_cursor=len_read+strlen(print_hist);
										fflush(stdout);
										last_com_len=strlen(print_hist);
										strcpy(current_command,print_hist);
										cursor=(int)(strlen(printf_stat))+last_com_len;
										current_com_len=last_com_len;

									}
								}
								break;
							}
						case 'C':
							{
								//printf("right\n");
								break;
							}
						case 'D':
							{
								//printf("left\n");
								break;
							}
					}
				}
				//keystroke finished
				else if(key==127||key==8)
				{
					//printf("here");
					if(key==127&&cursor>len_read)
					{
						printf("\33[2K\r");
						printf("%s",printf_stat);
						//printf("\b \b",key,key);
						fflush(stdout);
						cursor--;
			       current_command[current_com_len-1]='\0';							
						current_com_len--;
						if(show_current==history_count+1)
						{
							*(shell_command+inp_iter-1)='\0';
							inp_iter--;
						}
						printf("%s",current_command);
					}

					//ungetc(shell_command[inp_iter-1],stdin);
				}
				else
				{
					cursor++;
					current_command[current_com_len++]=key;
					current_command[current_com_len]='\0';

					if(show_current==history_count+1)
					{
						*(shell_command+inp_iter++)=key;
						*(shell_command+inp_iter)='\0';
					}
					printf("%c",key);
					fflush(stdout);
					//	strcpy(current_command,shell_command);
				}

			}
			printf("\n");
			//	if(history_count+1!=show_current)
			//	{
			//		strcpy(shell_command,print_hist);
			//		inp_iter=strlen(print_hist);
			//	}
			//		current_command[strlen(current_command)]='\0';
			len_read=inp_iter;
			strcpy(shell_command,current_command);
			//read complete
			//save in history

			//save_history(shell_command);
			//printf("%s %s",current_command,shell_command);
			if(strcmp(current_command,"")==0)
			continue;
			
			if((his_child=fork())==0)
			{
				execlp("myhistory","myhistory",shell_command,NULL);
				exit(0);
			}
			else
			{	
				waitpid(his_child,&hstatus,WIFEXITED(&hstatus));

				history_count++;
			}


			//finished maintaining history
//starting pipe handling
			if(len_read==-1)
				printf("err");
			else
			{
				int mit,pipe=0;
				char pit[4];
				for(mit=0;mit<strlen(shell_command);mit++)
				{
					if(shell_command[mit]=='|')
					{	pipe=1;
						strcpy(pit,"|");
						break;
					}

				}
				if(!pipe)
					strcpy(pit," \n");
				//parse the command and its arguements

				token=strtok(shell_command,pit);

				num_param=0;
				if(pipe)
				{//setenv("HOME",pipe_file,1);
					param[num_param]=(char *)malloc(sizeof(char)*strlen("mypipe"));
					strcpy(param[num_param],"mypipe");
					//param[num_param]=token;
					num_param++;

				}
				if(token==NULL)
					continue;

				while(token!=NULL)
				{
					param[num_param]=(char *)malloc(sizeof(char)*strlen("mypipe"));

					param[num_param]=token;
					num_param++;
					//      printf("%s\n",param[num_param-1]);
					token=strtok(NULL,pit);

				}
				param[num_param]=(char *)malloc(sizeof(char)*strlen("mypipe"));
				*(param+num_param)=NULL;
				//parsing fininished

				if(strcmp(param[0],"exit")==0)
				{
					break;
				}
				do_execute(param,num_param);



			}
			//else above    



			//      break;

		}
		//while(1) above
//		system("rm .history");



		return 0;
	}





















