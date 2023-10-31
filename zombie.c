#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

int main(int argc, char const *argv[])
{
	/* A child dies, but the parent, uncaring */
	/* Dying before he retrives his child's code */
	/* The reaper, undying, from the burden he's bearing */
	/* He must now take care of his soul */
	pid_t pid = fork();
	if(pid == 0){
		printf("I am the child and i will die.\n");
		sleep(2);
		return 0;
	}
	sleep(5);
	// printf("\n");
	// int st;
	// waitpid(pid, &st, 0);
	return 0;
}