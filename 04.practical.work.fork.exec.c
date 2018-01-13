#include<unistd.h>
#include<stdio.h>

int main()
{
	printf("Main before fork()\n");
	int pid1 = fork();
	if (pid1 == 0)
	{
		int pid2 = fork();
		if (pid2 == 0)
                { 
 			printf("I am child after fork(), launching free -h\n");
                        char *args1[] = {"free", "-h", NULL};
                        execvp("free", args1);
		}
		else 
		{
			printf("I am child after fork(), launching ps -ef\n");
                        char *args2[] = {"/bin/ps", "-ef", NULL};
                        execvp("/bin/ps", args2);
		}
	}
	return 0;
}
