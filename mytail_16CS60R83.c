#include<stdio.h>
#include<string.h>
#include<time.h>
#include<malloc.h>
#define SIZE 200

//command syntax: mytail -13 file
int main(int argc,char **argv)
{
	FILE *read_file;
	int num_lines=0,i=0,count=0;
	long long int total_char;
	char str[SIZE];
    char **str_cp;
	size_t len;
	int z,ct;   
	char character;
	if(argc<2)
	{
		printf("Few arguements\n");
		return 0;
	}
	if(argc==2)
	{
		FILE *fp=stdin;
		if(fp==NULL)
		{
			printf("error2\n");
			return 0;
		}
		argv[argc]=(char *)malloc(sizeof(char)*256);
		strcpy(argv[argc],"stdin");
		argc++;
		argv[argc]=NULL;
	}
	for(i=1;i<strlen(argv[1]);i++)
	{
		num_lines+=(int)(argv[1][i]-'0');
		if(i!=strlen(argv[1])-1)
			num_lines*=10;
	}
	if(strcmp(argv[2],"stdin")==0)
	{
	

	 z=0;

 ct=0;	
character=getc(stdin);

	//read_file=fopen(stdin,"rb");
		str_cp[z]=(char *)malloc(sizeof(char)*1024);
		while (EOF != character) {

			//while(c(getline(&str[z-1],&len,read_file)<0))
			//	{
			//if(num_lines==z)

			if(character=='\n')
			{
				str_cp[z][ct]=character;
				str_cp[z][ct+1]='\0';
				z++;
				str_cp[z]=(char *)malloc(sizeof(char)*1024);	
				ct=0;

			}
			else
			{
				str_cp[z][ct++]=character;
			}
			character=getc(stdin);
		}
		if(strlen(str_cp[z])==0)
		str_cp[z--]=NULL;
		else
		str_cp[z][ct]='\0';
		int kc=1;
		while(z>=0&&kc!=num_lines)
		{
			printf("%s",str_cp[z--]);
			kc++;

		}
		printf("\n");	
		return 0;
	}
		else
		{
			read_file=fopen(argv[2],"r");
			if(read_file==NULL)
			{printf ("File does not exists\n");
				return 0;
			}
		}
		fseek(read_file, 0, SEEK_END);
		total_char = ftell(read_file);

		// search for '\n' characters
		while (total_char)
		{
			if (!fseek(read_file, --total_char, SEEK_SET))
			{
				if (fgetc(read_file) == '\n')

					if (count++ == num_lines)
						break;
			}
		}
		if(total_char==0)
			fseek(read_file,total_char,SEEK_SET);
		while (fgets(str, sizeof(str), read_file))
			printf("%s", str);

		printf("\n");
	}
