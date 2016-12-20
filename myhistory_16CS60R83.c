#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
int main(int argc,char **argv)
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
fprintf(fp,"%s",argv[1]);

fclose(fp);
//str=(char *)malloc(sizeof(char)*1024);
//done=getline(&str,&allo,fp);
//if(done<0)
//printf("Error\n");
//{



//}


exit(0);
}
