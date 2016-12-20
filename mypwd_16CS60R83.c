#include<unistd.h>
#include<stdio.h>
#include<malloc.h>
#define dir_len 256


void get_directory(char *cwd)
{
getcwd(cwd,dir_len+1);
puts(cwd);
}



int main(int argc,char **argv)
{

char * dir_name;
if(argc>1)
{
printf("Error: too many arguements\n");
return 0;
}
dir_name=(char*)malloc((sizeof(char))*(dir_len+1));
get_directory(dir_name);
return 0;

}
