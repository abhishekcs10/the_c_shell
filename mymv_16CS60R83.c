#include<stdio.h>
int main(int argc,char **argv)
{

	int status;
	if(argc<3)
		printf("Syntax error");
	else if (argc>3)
		printf("Too many arguements");
	else
	{
		status=rename(argv[1],argv[2]);
		if(status)
			printf("Error\n");
	}

	return 0;
}
