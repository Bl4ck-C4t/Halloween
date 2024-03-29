
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/prctl.h> 
#include <sys/wait.h>
#include <syslog.h>

/* He's stood there unyielding, observing, uncertain */
/* No proccess, but him, could carry such burden */
/* The codes of the damned and the orphaned he reaps */
/* The system of clutter and death he now cleans */

static void skeleton_daemon()
{
    pid_t pid;

    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    // signal(SIGCHLD, SIG_IGN);
    // signal(SIGHUP, SIG_IGN);

    /* Fork off for the second time*/
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    
    prctl(PR_SET_CHILD_SUBREAPER, 1); // become reaper

    /* Set new file permissions */
    umask(0);

    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    chdir("/");
    
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    /* Close all open file descriptors */

    /* Open the log file */
    openlog("TheReaper", LOG_PID, LOG_DAEMON);
}


void handle_zombies(){
	int status;
    pid_t pid = wait(&status);
    char buff[300];
    sprintf(buff, "Reaped process with pid %d, status: %d\n", pid, status);
    syslog(LOG_NOTICE, buff);
}

int main()
{
    skeleton_daemon(); // turn into demon

    syslog (LOG_NOTICE, "The Reaper is here.");
    pid_t pid = fork();
    if(pid > 0){
    	signal(SIGCHLD, handle_zombies);
    }
    if(pid == 0){
    	char * prog = "/home/bl4ckc4t/Halloween/graveyard"; // point this to the graveyard
    	execl(prog, prog, (char*)NULL);
    	sleep(5);
        syslog(LOG_NOTICE, "Terminated\n");
    	return 0;
    }

    int status;

    handle_zombies(); // reap direct child

    sleep(20);

    syslog (LOG_NOTICE, "The Reaper is gone.");
    closelog();

    return EXIT_SUCCESS;
}