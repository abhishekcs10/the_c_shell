
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
int search_pattern(char *text, char *pattern){

	int i,len=strlen(text),text_iter=0,pat_iter=0,ans=0;

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
				continue;
			}
			else
			{
				text_iter++;
			}
		}

		if(pat_iter==strlen(pattern))
		{ans=1;
			return 1;
		}

	}



	return 0;
}

/*
solve_plus:This function resolves the r+ regular expression into rr* form and replaces r*r to rr* to make the string right recursive
arguements: takes the text string (no use in this funtion except to pass to search_pattern function) and modified pattern having no ? in the pattern
*/

int solve_plus(char *text,char *keep_modified)
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
	//int i=0,z=0;
	//char *modified=(char *)malloc(sizeof(char)*strlen(str));
	//for(;i<mod1;i++)
	//{
	//if(str[i]!='*')
	//modified[z++]=str[i];
	//else
	//{
	//modified[z]='\0';
	//printf("%s\n",str);
	answer=search_pattern(text,str);
	fin_an|=answer;
	if(fin_an)
		return 1; //return 
	//}

	//}

	return 0;

}

/*
recomp-> this function generates all possible combinations of strings for ? sign (if neccessary)

takes input the text string and pattern to be modified
*/
int recomp(char *text,char *keep_modified){

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
		ans=solve_plus(text,hoga);
		//fin=solve_plus(text,nahi_hoga);
		return ans;
	}
	else
	{
		//printf("%s\n",hoga);
		//printf("%s\n",nahi_hoga);

		ans=recomp(text,hoga);
		if(ans)
			return 1;

		fin=recomp(text,nahi_hoga);
		if(fin)
			return 1;
	}
}

/*
This funtion is to handle various cases defined by problem statement

*/
void search(int argc,char **argv,int mode,int num_lines) //mode 0 normal mode 1-> count matches mode2-> invert 
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
	if(mode==0)
	{file_no=2;
		strcpy(pattern,argv[1]);
	}   
	else if(mode==2)
	{file_no=3; 
		strcpy(pattern,argv[2]);
	}   
	else
	{file_no=4;
		strcpy(pattern,argv[3]);
	}

	for(;file_no<argc;file_no++)
	{
		if(strcmp(argv[file_no],"stdin")==0)
		fp=stdin;
		else
		{		
		fp=fopen(argv[file_no],"r");
		if(fp==NULL)
			printf("Error reading file %s\n",argv[file_no]);
		}

		while((read_char=getline(&read_line,&line_size,fp))!=-1){
			//read_line[strlen(read_line)-1]='\0';
			compile_status=recomp(read_line,pattern);//return 1 on success
			if(compile_status==-1)
			{
				fprintf(stderr,"Could not compile pattern to be searched\n");
				exit(1);
			}
			if(compile_status)
			{
				if(mode!=2)
				{
					count_match++;
					printf("%s",read_line);
					if(mode==1&&count_match==num_lines)
						return;
				}
				else
					continue;
			}
			else if(!compile_status){
				if(mode==2)
				{
					printf("%s",read_line);
				}
				else
					continue;
			}
			else{
				//               regerror(compile_status,&compiled_pattern,msg_buffer,sizeof(msg_buffer));
				//             fprintf(stderr," Failed: %s\n",msg_buffer);
				exit(1);
			}

		}

	}
	free(pattern);
	free(read_line);

}


int main(int argc,char **argv)
{
	/*    //searching variables
		  char *text,*pattern;
		  size_t text_mem=100004,pat_mem=1001;
		  ssize_t text_scan,pat_scan;
		  text=(char *)malloc(sizeof(char)*text_mem);
		  pattern=(char *)malloc(sizeof(char)*pat_mem);
		  text_scan=getline(&text,&text_mem,stdin);
		  pat_scan=getline(&pattern,&pat_mem,stdin);
		  text[strlen(text)-1]='\0';
		  pattern[strlen(pattern)-1]='\0';
	//printf("%d\n",search_pattern(text,pattern));
	int ans=recomp(text,pattern);
	printf("%d\n",ans);
	//variable finished
	 */
	if(argc<2)
	{   
		printf("error\n");
		return 0;
	}
	else if(argc==2)
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
		search(argc,argv,0,-1);
	}
	else if(strcmp(argv[1],"-m")==0) //count upto m number
	{    
		int num_lines=0,i;
		for(i=0;i<strlen(argv[2]);i++)
		{
			num_lines*=10;
			num_lines+=(int)(argv[2][i]-'0');

		}
		if(argc<4)
		{
			printf("Error Syntax\n");
			return 0;
		}
		if(argc==4)
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
		search(argc,argv,1,num_lines);
	}
	else if(strcmp(argv[1],"-v")==0){   //invert match
		if(argc<3)
		{
			printf("Error Syntax\n");
			return 0;
		}
		if(argc==3)
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
		search(argc,argv,2,-1);
	}
	else{
		search(argc,argv,0,-1);
	}
	return 0;
}




