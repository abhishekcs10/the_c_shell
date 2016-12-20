
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
Author: Abhishek Tiwari
File: mygrep_16CS60R83
 */

/* This function searches for pattern of the form
   S->aS|a
   a->{set of terminals}
arguements: text string in which pattern is to be searched
pattern: simplified regular expression
 */
/*int str_to_num(char *str)
{
int len=strlen(str),iterate=0,num=0;
if(str[0]=='-')
iterate=1;
for(;iterate<len;iterate++)
{
num*=10;
num+=(int)(str[iterate]-'0');

}
if(str[0]=='-')
{
num=-num;
}
return num;

}
*/

int search_pattern(char *text, char *pattern,char *replace,int count_n,FILE *fp2)
{

	int i,len=strlen(text),text_iter=0,pat_iter=0,ans=0,start_index=0,rep_len=strlen(replace),new_cpy=0,last_index=0,cpy=0,found=0,pat_no=0;
	char *new_text=(char *)malloc(sizeof(char)*(len*strlen(replace)));
//	FILE *fp=fopen(".edited2","a");
new_text[0]='\0';
	for(;text_iter<len;)
	{
		if(text[text_iter]==pattern[pat_iter])
		{
			pat_iter++;
			text_iter++;
			if(pattern[pat_iter]=='*')
			{
				while(text[text_iter]==text[text_iter-1])
					text_iter++;
				pat_iter++;
			}
		}
		else if(text[text_iter]!=pattern[pat_iter]&&pattern[pat_iter+1]=='*')
		{
			pat_iter+=2;
		}
		else
		{
			pat_iter=0;
			if(text[text_iter]==pattern[pat_iter])
			{
				start_index=text_iter;
				continue;
			}
			else
			{
				start_index=text_iter+1;
				text_iter++;
			}
		}

		if(pat_iter==strlen(pattern))
		{pat_no++;
			if(count_n==-2)
			{
			found=1;
			return 1;
			}
		else if(count_n==-1)
			{
			found=1;
			for(cpy=last_index;cpy<text_iter;cpy++)
			{
				if(cpy==start_index)
				{strcat(new_text,replace);
					new_cpy=strlen(new_text);
					cpy+=text_iter-start_index-1;
				}
				else
				{new_text[new_cpy++]=text[cpy];
				new_text[new_cpy]='\0';
				
			}
			new_text[new_cpy]='\0';
			last_index=text_iter;
			printf("%s\n",new_text);
			}
			else 
			{
			if(pat_no==count_n)
				{found=1;
	for(cpy=last_index;cpy<text_iter;cpy++)
			{
				if(cpy==start_index)
				{strcat(new_text,replace);
					new_cpy=strlen(new_text);
					cpy+=text_iter-start_index-1;
				}
				else
				new_text[new_cpy++]=text[cpy];
			}
			new_text[new_cpy]='\0';
			last_index=text_iter;
//			printf("%s\n",new_text);
				}

			}
		//	return 1;
		}

	}
if(found&&count_n!=-2)
{
for(cpy=last_index;cpy<len;cpy++)
{

new_text[new_cpy++]=text[cpy];

}
new_text[new_cpy++]='\0';
printf("%s\n",new_text);
fputs(new_text,fp2);
free(new_text);
return 1;
}

	return 0;
}


