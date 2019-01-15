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
	sleep(10);
	printf("Still running\n");
	// int st;
	// waitpid(pid, &st, 0);
	return 0;
}