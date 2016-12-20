//This part of code contains deleting lines from a file
//the structure is for creating a list of line number that is to be deleted
struct num_token{
	int token_number;
	struct num_token *next;
};


//this is for merge sort splitting list into two haves
void splitList( struct num_token* source, struct num_token** frontRef,struct num_token** backRef)
{
	struct num_token* fast;
	struct num_token* slow;
	if (source==NULL || source->next==NULL)
	{
		/* length < 2 cases */
		*frontRef = source;
		*backRef = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;

		/* Advance 'fast' two nodes, and advance 'slow' one node */
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}

		/* 'slow' is before the midpoint in the list, so split it in two
		   at that point. */
		*frontRef = source;
		*backRef = slow->next;
		slow->next = NULL;
	}

}
struct num_token* merge(struct num_token *a,struct num_token *b){
	struct num_token* result=NULL;
	if(a==NULL)
		return b;
	else if (b==NULL)
		return(a);

	/* Pick either a or b, and recur */
	if (a->token_number <= b->token_number)
	{
		result = a;
		result->next = merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = merge(a, b->next);
	}
	return(result);

}
//to sort the link list
void sort(struct num_token** get_list)
{
	struct num_token *head=*get_list;
	struct num_token *a;
	struct num_token *b;
	if((head==NULL)||(head->next==NULL))
		return;

	splitList(head,&a,&b);

	sort(&a);
	sort(&b);

	*get_list= merge(a,b);

}


//converting string to integer
int str_to_num(char *str)
{
	int len=strlen(str),iterate=0,num=0;
	for(iterate=0;iterate<len;iterate++)
	{
		num*=10;
		num+=(int)(str[iterate]-'0');

	}

	return num;

}

//make changes in file according to given format
void edit_file(FILE *source,FILE *dest,struct num_token** line,int mode,int note){

	char *read_line;
	size_t sizeofline;
	ssize_t read_char;
	int line_doing=0;
	struct num_token *ok=*line;
	read_line=(char *)malloc(sizeof(char)*1024);
	while((read_char=getline(&read_line,&sizeofline,source))!=-1){
		
if(mode==0)
{
if(!note)
	{
		line_doing++;
		if(ok!=NULL&&line_doing==ok->token_number)
		{
			ok=ok->next;
			continue;
		}
		else
			fputs(read_line,dest);
}
else{
		line_doing++;
		if(ok!=NULL&&line_doing==ok->token_number)
		{
			ok=ok->next;
			fputs(read_line,dest);
		}
		else
			continue;

}
}
else{

int ind,from=ok->token_number,to=ok->next->token_number;
if(!note)
{
line_doing++;
if(line_doing>=from&&line_doing<=to)
continue;
else
fputs(read_line,dest);

}
else
{
line_doing++;
if(line_doing<from||line_doing>to)
continue;
else
fputs(read_line,dest);


}
}
}
//end
}

//parse file and delete lines
void delete_lines(int argc,char **argv){

	if(argv[1][1]=='['||argv[1][1]=='\\')
	{
		int note=0;
		if(argv[1][1]=='\\')
		note=1;
		int dots=0,dk,mode=0;


		char *token;
		char *test_str;
		int len;
		struct num_token *token_alot,*head=NULL,*join;
		int file_no,tk_no=0,sorted=1;
		test_str=(char *)malloc(sizeof(char)*strlen(argv[1]));

		if(note)
		strcpy(test_str,argv[1]+3);
		else
		strcpy(test_str,argv[1]+2);
		len=strlen(test_str);
		test_str[len-1]='\0';
		len--;
		test_str[len-1]='\0';
		len--;
		test_str[len-1]='\0';
		len--;
		for(dk=0;dk<len-2;dk++)
		{
			if(test_str[dk]=='.'&&test_str[dk+1]=='.'&&test_str[dk+2]=='.')
			{
				test_str[dk]='\0';
				dots=1;
				mode=1;
				break;
			}
		}
		if(dots)
		{
			int from=0,to=0;
			from=str_to_num(test_str);
			to=str_to_num(test_str+dk+3);
			token_alot=(struct num_token *)malloc(sizeof(struct num_token));
			token_alot->token_number=from;
			token_alot->next=NULL;
			head=token_alot;
			token_alot=(struct num_token *)malloc(sizeof(struct num_token));
			token_alot->token_number=to;
			head->next=token_alot;
			token_alot->next=NULL;

		}
		else
		{
			token=strtok(test_str," ,\n");
			if(token==NULL)
				return;
			while(token!=NULL)
			{
				token_alot=(struct num_token *)malloc(sizeof(struct num_token));
				token_alot->token_number=str_to_num(token);
				token_alot->next=NULL;
				if(!tk_no)
				{
					head=token_alot;
					join=head;
				}
				else
				{
					if(token_alot->token_number<join->token_number)
						sorted=0;
					join->next=token_alot;
					join=token_alot;
				}
				tk_no++;
				token=strtok(NULL," ,\n");
			}
			if(!sorted)
				sort(&head);
		}

		FILE *fp2=fopen(".edited","w");
		FILE *fp=fopen(argv[2],"r");
		edit_file(fp,fp2,&head,mode,note);
		
		fclose(fp);
		fclose(fp2);
		remove(argv[2]);		
		rename(".edited",argv[2]);
		
	}
	//ended [ case


	return;
}


