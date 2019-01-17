#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

int main(int argc, char const *argv[])
{
	pid_t pid = fork();
	if(pid > 0){
		return 0;
	}
	// sleep(6);
	printf("Still running\n");
	setsid();
	sleep(5);
	// int st;
	// waitpid(pid, &st, 0);
	return 0;
}