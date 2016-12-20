
#include<unistd.h>
#include<stdio.h>
#include<malloc.h>
#define dir_len 256

/*
   void change_directory(char *cwd)
   {
   if(chdir(cwd)==0)
   {
   puts(cwd);
   }
   else
   {
   puts("Directory does not exist");
   }
   }

 */

int main(int argc, char **argv)
{

	int iter;
	FILE *fp;
	if(chdir(argv[1])==-1)
		printf("Error Changing Directory\n");
//changed directory path is stored in file and is set though setenv command in myshell program
	fp=fopen("change","w");
	fprintf(fp,"%s",argv[1]);


	return 0;

}
