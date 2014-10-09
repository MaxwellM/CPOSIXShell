#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <sys/procfs.h>

int myPs(){
	FILE *fp;
	//int status;
	char path[1035];

	/* Open the command for reading. */
	fp = popen("/bin/ps", "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		//exit;
	}
	/* Read the output a line at a time - output it. */
	while (fgets(path, sizeof(path), fp) != NULL) {
		printf("%s", path);
	}

	/* close */
	pclose(fp);

	return 0;
}

int myTop(){
	FILE *fp;
	//int status;
	char path[1035];

	/* Open the command for reading. */
	fp = popen("/usr/bin/top", "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		//exit;
	}
	/* Read the output a line at a time - output it. */
	while (fgets(path, sizeof(path), fp) != NULL) {
		printf("%s", path);
	}

	/* close */
	pclose(fp);

	return 0;
}

int myPwd()
{
	char buffer[100];
	if(getcwd(buffer,sizeof(buffer)))//Get current working directory and store it in buffer.
	{
		printf("%s\n",buffer);
	}
	else
	{
		perror("getcwd");//Display the error occurred with getcwd.
	}
	return 0;
}

int myLs(){
	DIR *d;
	struct dirent *dir;
	d = opendir(".");
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			printf("%s\n", dir->d_name);
		}
		closedir(d);
	}
	return 0;
}

int myCd(char *args[]){
	if (args[1] != 0){
		chdir(args[1]);
	}
	return 0;
}

void setArgs(char buf[],char *args[]){
	//Finds everything up till the first white space
	char *temp1;
	temp1 = strchr(buf,(int)' ');
	if (temp1 != NULL){
		printf("1st temp done\n");
		*temp1 = NULL;
		args[0] = buf;
		temp1++;
		while(*temp1 == (int)' ' && *temp1 != NULL){
			temp1++;
		}
		//Finds everything from the first whitespace to the second
		char *temp2;
		temp2 = strchr(temp1,(int)' ');
		if(temp2 != NULL){
			*temp2 = NULL;
			args[1] = temp1;
			temp2++;
			while(*temp2 == (int)' ' && *temp2 != NULL){
				*temp2 = NULL;
				temp2++;
			}
			args[2] = temp2;
		}
		else{
			args[1] = temp1;
		}
	}
	else{
		args[0] = buf;
	}
}




int main(int argc, char *argv[])
{
	char buf[80] ;
	char *ptr ;
	char path[80] ;
	char dir[80];
	char *test;
	int run = 1;	//shell and children will run until

	int i, pid ;
	char *args[3] ;


	printf ("Hello! I'm Sheldon, the C Posix Shell.\n"
			"I accept the following Linux commands: ls - pwd - top\n"
			"Type 'help' in the command line at any time!\n\n");


	while (run){ //Begin while run
		printf("Give me a command\n");
		printf(">>\n");
		read(0, buf, 80) ; //stdin
		ptr = buf;
		while (*ptr != '\n'){
			ptr++ ;
		}
		*ptr = NULL;
		printf("\n") ;

		setArgs(buf, args);
		pid = fork();

		if (pid == 0)
		{
			//printf("buf[0] = %c, buf[1] = %c, buf[2] = %d\n",buf[0],buf[1],buf[2]);
			printf("buf = %s\n",buf);

			if(strcmp(buf,"ls") == 0){
				//Get everything in current directory and print
				printf("This should print...\n");
				myLs();
			}
			else if(strcmp(buf,"pwd") == 0){
				printf("This should print...\n");
				printf(myPwd());
				//printf("Current path: %s\n",args[0]);
			}
			else if(strcmp(buf,"top") == 0){
				//not a clue what to do here
				printf("This should print TOP...\n");
				printf(myTop());
			}
			else if(strcmp(buf,"ps") == 0){
				//displays active processes (non interactive)
				printf("This should print PS...\n");
				printf(myPs());
			}
			else{
				printf("This should run something...\n"
						"%s\n",args[0]);
				args[1] = NULL;
				args[2] = NULL;
				printf("%d", args[2]);
				execv(args[0], args);
			}

			run = 0; //Let child die
		}

		else{
			wait() ;
			if(strcmp(buf, "exit") == 0){
				printf("Big Gulps huh? Whelp, see ya later....");
				run = 0;
			}
			else if(strcmp(args[0],"cd") == 0){
				//change working directory
				printf("This should print...\n");
				myCd(args);

			}
		}
	}//End while run
}

