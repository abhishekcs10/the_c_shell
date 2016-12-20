#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>

int countEntriesInDir(const char* dirname)
{
	int n=0;
	struct  dirent* d;
	DIR* dir = opendir(dirname);
	if (dir == NULL) return 0;
	while((d = readdir(dir))!=NULL) n++;
	closedir(dir);
	return n;
}

void removeRec(char *dir){

	struct dirent *dir_st;
	DIR *directory; 
	int n=0,i,status=0;
	struct stat file_stat;
	char buff[256],pass[256];
	int patlen;
	if(dir[0]!='/')
	{getcwd(buff,255);
		strcat(buff,"/");
	}
	strcat(buff,dir);
	strcat(buff,"/");
	directory=opendir(dir);
	patlen=strlen(buff);
	strcpy(pass,dir);
	while((dir_st=readdir(directory))!=NULL)
	{
		buff[patlen]='\0';
		if(strcmp(dir_st->d_name,".")==0||strcmp(dir_st->d_name,"..")==0)
			continue;
		strcat(buff,dir_st->d_name);
		if(stat(buff,&file_stat)<0)
			return ;
		if(S_ISREG(file_stat.st_mode))
			remove(buff);
		else if(countEntriesInDir(buff)<=2)
			rmdir(buff);
		else
		{
			strcat(pass,"/");
			strcat(pass,dir_st->d_name);
			removeRec(pass);

		}
	}
	closedir(directory);
	rmdir(dir);
}



int main(int argc,char ** argv)
{
	struct dirent *dir_st;
	DIR *directory; 
	int n=0,i,status=0;
	struct stat file_stat;
	char buff[256];
	if(argc<2)
	{
		printf("Error:no arguements\n");
	}
	if(strcmp(argv[1],"-d")==0)
	{

		directory=opendir(argv[2]);
		if(directory==NULL)
		{printf("directory does not exist");
			return 0;
		}
		closedir(directory);
		/*
		   while((dir_st=readdir(directory))!=NULL)
		   {
		   if(++n>2)
		   break;
		   }
		   closedir(directory);
		 */
		status=0;
		//if(n<=2)
		//{
		status=rmdir(argv[2]);
		if(status)
		{
			printf("directory is not empty\n");
		}
		return 0;
	}
		else if(strcmp(argv[1],"-r")==0)
		{

			removeRec(argv[2]);

		}

		else
		{

			for(i=1;i<argc;i++)
			{
				status=0;
				status=remove(argv[i]);
				if(status!=0)
					printf("Errot cannot remove file %s\n",argv[i]);

			}



		}



		return 0;
	}

