
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/prctl.h> 
#include <sys/wait.h>
#include <syslog.h>


/* The system would burn, the resources will blow */
/* The reaper takes all that has left him it's toll */
/* He waits for the children and heeds to their call */
/* When status codes come, resources will flow */

void handle_zombies(){
    int status = -1;
    pid_t pid = waitpid(-1, &status, 0);
    printf("Received SIGCHILD with pid %d, status: %d\n", pid, status);
}

int main(int argc, char const *argv[])
{
    printf("I am reaper, my pid is %d, my dad is %d\n", getpid(), getppid());
    pid_t parent = fork();
    if (parent == 0){
    	pid_t child = fork();
    	if(child > 0){
    		printf("I am parent, my pid is %d\n", getpid());
    		sleep(3);
    		return 15;
    	}

        child = fork();
        if(child > 0){
            sleep(5);
            return 20;
        }

		printf("I am the child. my pid is %d\n", getpid());
    	printf("My dad is %d\n", getppid());
		sleep(7);
		// printf("My new dad is %d\n", getppid());
    	return 13;
    	

    }
    else{
        prctl(PR_SET_CHILD_SUBREAPER, 1);
    	int status;
        wait(&status);
        printf("Reaped process, got soul: %d\n", WEXITSTATUS(status));
        wait(&status);
        printf("Reaped process, got soul: %d\n", WEXITSTATUS(status));
        wait(&status);
        printf("Reaped process, got soul: %d\n", WEXITSTATUS(status));

    }
	return 0;
}