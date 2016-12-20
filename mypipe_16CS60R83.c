#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
int main(int argc, char **argv)
{
	int parse_proc,st;
	char *pwd;
	pwd=(char *)malloc(sizeof(char)*1024);
	//getcwd(pwd,sizeof(pwd));
	//setenv("PWD",pwd,1);
	//strcat(pwd,"/.output");
	char *dir=(char *)malloc(sizeof(char)*1024);
	pwd=getenv("HOME");
//	setenv("HOME",pwd,1);
		for(parse_proc=1;parse_proc<argc;parse_proc++)
	{
	char *token,*param[100];
	int num_param,cstatus;
//memset(pwd,0,strlen(pwd));
memset(dir,0,strlen(dir));
	strcpy(pwd,".output");
	sprintf(dir,"touch .out >/dev/null 2> /dev/null");
//	printf("%s",dir);
	fflush(stdout);
	system(dir);

	int file_disc[4];
	pid_t proc;
	pipe(file_disc);
	pipe(file_disc+2);
	
	//parse the command and its arguements
		token=(char *)malloc(sizeof(char)*1024);
		token=strtok(argv[parse_proc]," \n");
		num_param=0;
		if(token==NULL)
			return 0;

		while(token!=NULL)
		{
			param[num_param]=(char *)malloc(sizeof(char)*strlen(token));
			param[num_param]=token;
			num_param++;
			//      printf("%s\n",param[num_param-1]);
			token=strtok(NULL," \n");

		}
		param[num_param]=(char *)malloc(sizeof(char)*2);
		*(param+num_param)=NULL;

		//parsing fininished
if((file_disc[3]=open(pwd, O_CREAT|O_TRUNC|O_WRONLY,0644))<0)
{
perror(".output");
exit(1);
}


if((file_disc[2]=open(".out", O_RDONLY))<0)
{
perror(".output");
exit(1);
}

if(parse_proc==argc-1)
{
//dup2(file_disc[0],1);

execvp(param[0],param);

exit(1);
}
	else if((proc=fork())==0)
		{
//		FILE *new_file=fopen(
			
		//	dup2(file_disc[1],1);
			
			dup2(file_disc[3],1);	
			execvp(param[0],param);	
			exit(1);
		}
		else if(proc==-1)
		{
			printf("Error\n");
			exit(1);
		}
		else
		{
			waitpid(proc,&st,WIFEXITED(&st));
		}
		//dup2(file_disc[2],0);
		
		
		char coom[1024];
		sprintf(coom,"cat %s>./.out",pwd);
		system(coom);
		//sprintf(coom,"cat .out");
		//system(coom);
		dup2(file_disc[2],0);	
		//dup2(file_disc[0],0);
		close(file_disc[1]);
	}
//sprintf(pwd,"rm %s",pwd);
//system ("rm -r .output");
system("rm .out 2> /dev/null");
return 0;
}
