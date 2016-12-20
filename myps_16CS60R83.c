#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<malloc.h>
#include<stdlib.h>
#include<pwd.h>
#include<grp.h>

void get_proc_time(char proc_file[300])
{
	FILE *fp;
	char proc_user[256];


	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int i;
	struct passwd *pwd;
	long long int user_id=0;
	int hr,min,sec;
	strcat(proc_file,"/sched");
	fp=fopen(proc_file,"r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, fp)) != -1) {
		//printf("Retrieved line of length %zu :\n", read);
		if(line[0]=='s'&&line[1]=='e'&&line[2]=='.'&&line[3]=='s'&&line[4]=='u'&&line[5]=='m'&&line[6]=='_'&&line[7]=='e')
			break;

	}
	//		printf("%s\n", line);
	i=19;
	while(line[i]=='\t'||line[i]==' '||line[i]=='\n'||line[i]==':')
		i++;

	while(!(line[i]=='\t'||line[i]==' '||line[i]=='\n'||line[i]=='.'))
	{
		user_id+=(int)(line[i]-'0');
		user_id*=10;
		i++;
	}
	user_id/=10;
	//	pwd=getpwuid(user_id);
	//	if(pwd!=NULL)
	//		printf("\t%s",pwd->pw_name);
	//	else
	//		printf("\t");
	//printf("\tsss%d\t",user_id);
	user_id/=1000;
	hr=user_id/3600;
	user_id=user_id%3600;
	min=user_id/60;
	user_id=user_id%60;
	sec=user_id;
	if(hr/10==0)
		printf("%2s0%d:","",hr);
	else
		printf("%2s%d:","",hr);
	if(min/10==0)
		printf("0");
	printf("%d:",min);
	if(sec/10==0)
		printf("0");
	printf("%d",sec);

	//	printf("\t%2d:%2d:%2d\t",user_id%(3600000),user_id%(60000),user_id%(1000));
	fclose(fp);


}

void get_proc_name(char proc_file[300])
{
	FILE *fp;
	char proc_name[256];
	strcat(proc_file,"/comm");
	//process=opendir(proc_file);
	fp=fopen(proc_file,"r");


	if(fp!=NULL)
	{
		fscanf(fp,"%s",proc_name);
		printf("\t%s\n",proc_name);
	}

	fclose(fp);
}

int main(int argc, char **argv)
{
	DIR *dp,*process;
	struct dirent *sd;
	struct stat file_stat;
	int len,isdig=1,i,dir_len_p=0;
	FILE *fp;
	char proc_name[256],tty[256],tty_name[256];
	char proc_file[300]="/proc/";
	int enable_all=0;
	struct passwd *pwd;
	ssize_t ty;
	int status=0,pty=0;
	uid_t uid=getuid();
	dp=opendir("/proc");
	if(argc>2)
{
printf("Error: too many arguements\n");
return 0;
}

	printf("%5s ","PID");
	printf("TTY\t   TIME\t   USER\t\tPROCESS\n");

	while ((sd=readdir(dp))!=NULL)
	{
		proc_file[6]='\0';
		isdig=1;
		strcat(proc_file,sd->d_name);
		status=stat(proc_file,&file_stat);

		if(status||S_ISREG(file_stat.st_mode))
		{
			continue;
		}
		len=strlen(sd->d_name);
		for(i=0;i<len;i++)
		{
			if(sd->d_name[i]>='0'&&sd->d_name[i]<='9')
				continue;
			else
			{isdig=0;
				break;
			}
		}

		if(isdig==0)
			continue;

		pwd=getpwuid(file_stat.st_uid);
		proc_file[6]='\0';
		strcat(proc_file,sd->d_name);
		dir_len_p=strlen(proc_file);


		if(argv[1]!=NULL&& strcmp(argv[1],"-a")==0)
		{
			printf("%5s ",sd->d_name);
			//	get_proc_time(proc_file);

			strcat(proc_file,"/fd/0");
			ty=readlink(proc_file,tty,20);
			if(ty<0)
				printf("%s\t","?    ");
			else
			{
				for(pty=5;pty<11;pty++)
				{
					tty_name[pty-5]=tty[pty];
				}
				if(tty_name[0]=='t'&&tty_name[1]=='t'&&tty_name[2]=='y')
				{

					tty_name[4]='\0';


					printf("%s\t",tty_name);
				}


				else if((tty_name[0]=='p'&&tty_name[1]=='t'&&tty_name[2]=='s'))
				{		
					tty_name[5]='\0';

					printf("%s\t",tty_name);
				}
				else
					printf("%s\t","?     ");

			}		

			proc_file[dir_len_p]='\0';

			get_proc_time(proc_file);
			if(pwd!=NULL)
				printf(" %s ",pwd->pw_name);
			else
				printf(" %s   ","");

			proc_file[dir_len_p]='\0';

			get_proc_name(proc_file);
			proc_file[dir_len_p]='\0';
		}

		else if(argv[1]==NULL)
		{

			if(file_stat.st_uid==uid)
			{
				printf("%5s ",sd->d_name);
				//	get_proc_tty(proc_file);

				strcat(proc_file,"/fd/0");
				ty=readlink(proc_file,tty,20);
				if(ty<0)
					printf("%s\t","?    ");

				else
				{
					for(pty=5;pty<11;pty++)
					{
						tty_name[pty-5]=tty[pty];
					}
					if(tty_name[0]=='t'&&tty_name[1]=='t'&&tty_name[2]=='y')
					{

						tty_name[4]='\0';


						printf("%s\t",tty_name);
					}


					else if((tty_name[0]=='p'&&tty_name[1]=='t'&&tty_name[2]=='s'))
					{		
						tty_name[5]='\0';

						printf("%s\t",tty_name);
					}
					else
						printf("%s\t","?    ");


				}		



				proc_file[dir_len_p]='\0';



				get_proc_time(proc_file);
				if(pwd!=NULL)
					printf(" %s ",pwd->pw_name);
				else
					printf("  ");

				proc_file[dir_len_p]='\0';

				get_proc_name(proc_file);
				proc_file[dir_len_p]='\0';

			}


		}
		else{
			printf("Invalid option\n");
			break;
		}



	}


	return 0;
}
