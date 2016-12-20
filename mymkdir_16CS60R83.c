#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<malloc.h>
#include<sys/stat.h>
int main(int argc,char **argv)
{
	int i,status;
	struct stat dir_info;
	if(argc<2)
	{printf("Invalid syntax\n");
		return 0;

	}
	for(i=1;i<argc;i++)
	{
		//stat(argv[1],&dir_info);
		//if(S_ISDIR(dir_info.st_mode))
		//{
		//printf("E: error creating directory %s\n",argv[i]);
		//}
		//else
		//{
		status=mkdir(argv[i], 0755);
		if(status!=0)
			printf("E: %s directory cannot be created\n",argv[i]);


	}

	return 0;
	}
