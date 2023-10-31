#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

int main(int argc, char const *argv[])
{
	/* A parent has died and the child is alone */
	/* none will waitpid() for it's soul */
	/* Runs through the forest and tries to escape */
	/* For it's return to be reached, how long will it take? */

	pid_t pid = fork();
	if(pid == 0){
		pid_t pid = fork();
		if(pid > 0){
			sleep(2);
			return 0;
		}
		setsid();
		sleep(5);
		return 0;
	}
	// sleep(6);
	printf("Still running\n");
	sleep(8);
	// int st;
	// waitpid(pid, &st, 0);
	return 0;
}