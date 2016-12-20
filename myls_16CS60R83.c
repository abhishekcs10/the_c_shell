#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<time.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<dirent.h>
#include<malloc.h>
#include<pwd.h>
#include<grp.h>


void merge(int file_size,char words[][402],int start,int mid,int end)
{
	int left=mid-start+1;
	int right=end-mid,i,j;
	char word_l[1000][402],word_r[1000][402];
	for(i=0;i<left;i++)
	{
		strcpy(word_l[i],words[start+i]);
	}
	for( i=0;i<right;i++)
	{
		strcpy(word_r[i],words[mid+i+1]);
	}

	int k=start;
	for( i=0,j=0;i<left&&j<right;)
	{
		int cmp=strcmp(word_l[i],word_r[j]);
		if(cmp<=0)
		{
			strcpy(words[k++],word_l[i]);
			i++;
		}
		else{
			strcpy(words[k++],word_r[j]);
			j++;
		}

	}
	while(i<left)
	{
		strcpy(words[k++],word_l[i]);
		i++;

	}


	while(j<right) 
	{ 
		strcpy(words[k++],word_r[j]); 
		j++; 
	} 

} 

void sort(int file_size,char file[][402],int start,int end) 
{ 
	if(start==end) 
		return; 
	int mid=(start+end)/2; 
	sort(file_size,file,start,mid); 
	sort(file_size,file,mid+1,end); 

	merge(file_size,file,start,mid,end); 


} 



int main(int argc,char *argv[])
{
	struct stat info_dir;
	char *ddr,buff[256],file_nm[4024];
	struct group *grp;
	struct passwd *pwd;
	DIR *dp,*dp2;
	struct tm* timeinfo;
	int status,isd=0,i;
	struct dirent *sd; 
	char dirnames[1000][402];
	int num_dir=0;
	ddr=(char *)malloc(sizeof(char)*257);
	if(argv[1]==NULL)
	{getcwd(ddr,256);
		dp=opendir(ddr);
	}
	else
	{strcpy(ddr,argv[1]);
		dp=opendir(argv[1]);
	}

	status=stat(ddr,&info_dir);
	if(status)
	{
		printf("Error:not exists\n");
		return 0;

	}
	printf("%s:\n",ddr);

	while((sd=readdir(dp))!=NULL)
	{
		strcpy(dirnames[num_dir],sd->d_name);
		num_dir++;
	}
	printf("total: %d\n",info_dir.st_size*info_dir.st_blocks/info_dir.st_blksize);
	sort(num_dir,dirnames,0,num_dir-1);

	for(i=0;i<num_dir;i++)
	{
		status=0;
		strcpy(file_nm,ddr);
		if(file_nm[(strlen(ddr)-1)]=='/')
			strcat(file_nm,dirnames[i]);
		else
		{
			file_nm[strlen(ddr)]='/';
			file_nm[strlen(ddr)+1]='\0';
			strcat(file_nm,dirnames[i]);
		}

		if((dirnames[i][0])=='.')
			continue;

		status=stat(file_nm,&info_dir);
		if(status<0)
		{
			fprintf(stderr,"%s\n",dirnames[i]);
			return 1;
		}
		if(S_ISDIR(info_dir.st_mode))
			printf(	(S_ISDIR(info_dir.st_mode))?"d":"");
		else 
			printf("%s",S_ISLNK(info_dir.st_mode)?"l":"-");

		isd=S_ISDIR(info_dir.st_mode);
		printf((info_dir.st_mode & S_IRUSR)?"r":"-");
		printf((info_dir.st_mode & S_IWUSR)?"w":"-");
		printf((info_dir.st_mode & S_IXUSR) ? "x" : "-");
		printf((info_dir.st_mode & S_IRGRP) ? "r" : "-");
		printf((info_dir.st_mode & S_IWGRP) ? "w" : "-");
		printf((info_dir.st_mode & S_IXGRP) ? "x" : "-");
		printf((info_dir.st_mode & S_IROTH) ? "r" : "-");
		printf((info_dir.st_mode & S_IWOTH) ? "w" : "-");
		printf((info_dir.st_mode & S_IXOTH) ? "x" : "-");
		printf(" %2d ",info_dir.st_nlink);
		grp=(struct group *)malloc(sizeof(struct group));
		grp=getgrgid(info_dir.st_gid);
		//if(grp==NULL)
		//{printf("%d\n",);

		//}

		pwd=getpwuid(info_dir.st_uid);
		if(pwd==NULL||grp==NULL)
			printf("%6d %6d",info_dir.st_uid,info_dir.st_gid);
		else
			printf("%6s %6s",pwd->pw_name,grp->gr_name);
		printf("%8d",info_dir.st_size);
		timeinfo=localtime(&(info_dir.st_mtime));
		strftime(buff,sizeof(buff),"%b %d %H:%M",timeinfo);
		printf(" %s",buff);
		printf(" %s",dirnames[i]);
		if(isd)
			printf("/");
		printf("\n");

	}
	closedir(dp);
	return 0;
}


/*
   DIR *dp;
   char *ddr;
   struct dirent *sd; 
   ddr=(char *)malloc(sizeof(char)*257);
   if(argv[1]==NULL)
   {getcwd(ddr,256);
   dp=opendir(ddr);
   }
   else
   dp=opendir(argv[1]);
   while((sd=readdir(dp))!=NULL)
   {
   printf("%s\n",sd->d_name);
   }
   closedir(dp);
   }*/
