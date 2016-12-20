
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include "del_line_16CS60R83.h" //this file contains code for deleting lines
#include "permute_pattern_16CS60R83.h"	//this file contains code for forming permutations
#include "mygrep_16CS60R83.h"//this code cotains matching algorithm
//char *possible_patterns[1024],index_pat=0;

int main(int argc,char **argv)
{
	if(argv[1][1]=='\\'||argv[1][1]=='[')
	{
		delete_lines(argc,argv);
	}
	else if(argv[1][1]=='s'||argv[1][1]=='/')
	{
		strcpy(argv[1],argv[1]+1);
		argv[1][strlen(argv[1])-1]='\0';
		char *token,pit[4]="/";
		char *param[100],*file;
		int num_param=0,mode=0;
		//token=(char *)malloc(sizeof(char)*strlen(argv[1]));
		token=strtok(argv[1],"/");

		if(token==NULL)
			printf("NULL\n");
		//  continue;

		while(token!=NULL)
		{
			param[num_param]=(char *)malloc(sizeof(char)*(strlen(token)+1));
			strcpy(param[num_param],token);
			printf("%s\n",token);
			token=strtok(NULL,pit);
			num_param++;

		}
		*(param+num_param)=NULL;
		if(strcmp(param[num_param-1],"g")==0)
		{
			mode=1;
		}

		//grep(num_param,param);
		if(strcmp(param[0],"s")==0)		
		{
			//substitute(param[1],param[2],argv[2],-1,mode);
			search(1,param[1]);
			FILE *fp,*fp2;
			char *read_line;
			size_t line_size=100005;
			ssize_t read_char;
			read_line=(char *)malloc(sizeof(char)*line_size);
			fp=fopen(argv[2],"r");
			fp2=fopen(".edited2","w");
			if(fp==NULL)
				printf("Error\n");
			while((read_char=getline(&read_line,&line_size,fp))!=-1)
			{
				int ka,fond=0;
				for(ka=0;ka<index_pat;ka++)
				{
					if(mode==1)
						fond=search_pattern(read_line,possible_patterns[ka],param[2],-1,fp2);
					else
						fond=search_pattern(read_line,possible_patterns[ka],param[2],str_to_num(param[num_param-1]),fp2);

					if(fond)
						break;
					else
						fputs(read_line,fp2);
				}
			}
fclose(fp);
fclose(fp2);
				remove(argv[2]);		
		rename(".edited2",argv[2]);
		}
		else
		{
			FILE *fp,*fp2;
			char *read_line;
			size_t line_size=100005;
			ssize_t read_char;

				search(-1,param[0]);
				search(1,param[2]);
			fp=fopen(argv[2],"r");
			fp2=fopen(".edited2","w");
			if(fp==NULL)
				printf("Error\n");
		read_line=(char *)malloc(sizeof(char)*line_size);

			while((read_char=getline(&read_line,&line_size,fp))!=-1)
			{
				int isthere=0;
				int ka,fond=0;
				for(ka=0;ka<test_pat;ka++)
				{
					//if(mode==1)
					fond=search_pattern(read_line,testing_patterns[ka],"ok",-2,NULL);
					

					if(fond)
						break;
				}
				if(fond)
				{
					int searched=0;
	
					for(ka=0;ka<index_pat;ka++)
					{
						if(mode==1)
							searched=search_pattern(read_line,possible_patterns[ka],param[3],-1,fp2);
						else
							searched=search_pattern(read_line,possible_patterns[ka],param[3],str_to_num(param[num_param-1]),fp2);

						if(searched)
							break;
						else
							fputs(read_line,fp2);
					}

				}
				else
						fputs(read_line,fp2);
			}
fclose(fp);
fclose(fp2);

		remove(argv[2]);		
		rename(".edited2",argv[2]);

}

	}
	return 0;
}
