
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
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

char *possible_patterns[1024],index_pat=0,*testing_patterns[1024],test_pat=0,to_modi=0;

/*
solve_plus:This function resolves the r+ regular expression into rr* form and replaces r*r to rr* to make the string right recursive
arguements: takes the text string (no use in this funtion except to pass to search_pattern function) and modified pattern having no ? in the pattern
 */

int solve_plus(char *keep_modified)
{
	int iterate,answer=0,fin_an=0,ki=0;

	int len=strlen(keep_modified),mod=0,mod1=0,len_mod=0;
	char *str=(char *)malloc(sizeof(char)*2*len),*compiled=(char *)malloc(sizeof(char)*2*len);
	compiled[0]=keep_modified[0];
	mod++;
	for(iterate=1;iterate<len;iterate++)
	{
		if(keep_modified[iterate]=='+')
		{
			compiled[mod++]=keep_modified[iterate-1];
			compiled[mod++]='*';
		}
		else
			compiled[mod++]=keep_modified[iterate];
	}
	compiled[mod]='\0';


	strcpy(str,"");

	while(strcmp(compiled,str)!=0){
		if(ki==0)
		{ki=1;}
		else{
			strcpy(compiled,str);
		}
		mod1=0;
		str[0]=compiled[0];
		mod1++;
		len_mod=strlen(compiled);
		for(iterate=1;iterate<len_mod;iterate++)
		{
			if(iterate<len_mod-2&&compiled[iterate]=='*'&&(compiled[iterate-1]==compiled[iterate+1])&&compiled[iterate]==compiled[iterate+2]){
				str[mod1++]=compiled[iterate];
				while(iterate<len_mod-2&&compiled[iterate]=='*'&&(compiled[iterate-1]==compiled[iterate+1])&&compiled[iterate]==compiled[iterate+2])
					iterate+=2;
			}

			else if(iterate<len_mod-1&&compiled[iterate]=='*'&&(compiled[iterate-1]==compiled[iterate+1])){
				str[mod1++]=compiled[iterate+1];
				str[mod1++]='*';
				iterate+=1;
			}
			else{
				str[mod1++]=compiled[iterate];
			}
		}
		str[mod1]='\0';

	}
	if(!to_modi)
	{
possible_patterns[index_pat]=(char *)malloc(sizeof(char)*strlen(str));
	strcpy(possible_patterns[index_pat],str);
	index_pat++;
}
else{
testing_patterns[index_pat]=(char *)malloc(sizeof(char)*strlen(str));
	strcpy(testing_patterns[test_pat],str);
	test_pat++;

}

	return 1; //return 

	}

/*
   recomp-> this function generates all possible combinations of strings for ? sign (if neccessary)

   takes input the text string and pattern to be modified
 */
int recomp(char *keep_modified){

	int len=strlen(keep_modified),mod_hoga=0,mod_nahihoga=0;
	int iterate,noques=1,ans=0,fin=0,check=0;
	char *nahi_hoga=(char *)malloc(sizeof(char)*len);
	char *hoga=(char *)malloc(sizeof(char)*2*len);
	if(keep_modified[0]=='+'||keep_modified[0]=='?'||keep_modified[0]=='*')
		return -1;

	for(check=1;check<len;check++)
	{
		if((keep_modified[check]=='?'||keep_modified[check]=='+'||keep_modified[check]=='*')&& (keep_modified[check-1]=='?'||keep_modified[check-1]=='+'||keep_modified[check-1]=='*' ))
		{
			printf("Parsing Error: No concurrent symbols allowed..\n");
		}
	}

	if(len==0)
		return 1;
	hoga[mod_hoga++]=keep_modified[0];
	nahi_hoga[mod_nahihoga++]=keep_modified[0];
	for(iterate=1;iterate<len;iterate++)
	{
		if(keep_modified[iterate]=='?'&&noques)
		{
			//hoga[mod_hoga++]=keep_modified[iterate-1];
			mod_nahihoga--;
			noques=0;
		}
		else
		{
			hoga[mod_hoga++]=keep_modified[iterate];
			nahi_hoga[mod_nahihoga++]=keep_modified[iterate];
		}

	}
	hoga[mod_hoga]='\0';
	nahi_hoga[mod_nahihoga]='\0';
	if(noques)
	{
		//printf("%s\n",hoga);
		//printf("%s\n",nahi_hoga);
		ans=solve_plus(hoga);
		//fin=solve_plus(text,nahi_hoga);
		return ans;
	}
	else
	{
		//printf("%s\n",hoga);
		//printf("%s\n",nahi_hoga);

		ans=recomp(hoga);
		//		if(ans)
		//			return 1;

		fin=recomp(nahi_hoga);
		//		if(fin)
		//			return 1;

		return 1;
	}
}

/*
   This funtion is to handle various cases defined by problem statement

 */
void search(int argc,char *argv) //mode 0 normal mode 1-> count matches mode2-> invert 
{ 

	char *compiled_pattern;
	int compile_status,file_no,count_match=0;
	char msg_buffer[256];
	size_t line_size=100005;
	FILE *fp;
	char *read_line;
	ssize_t read_char;
	char *pattern;
	read_line=(char *)malloc(sizeof(char)*line_size);
	pattern=(char *)malloc(sizeof(char)*1005);
if(argc==-1)
to_modi=1;
else
to_modi=0;
file_no=2;
		strcpy(pattern,argv);

	compile_status=recomp(pattern);	
		free(pattern);
		free(read_line);

}







