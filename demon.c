
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/prctl.h> 
#include <syslog.h>

/* An orphaned child refusing to die */
/* It suffers and sits there in pain */
/* It's file descriptors are closed now, goodbye */
/* It sits in the system observing in vain */
static void skeleton_daemon()
{
    pid_t pid;

    /* Fork off the parent process */
    pid = fork();
    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);


    /* Success: Let the parent terminate */
    if (pid > 0){
        printf("A parent and a child.\n");
        sleep(3);
        printf("Parent dies. Child is orphan.\n");
        exit(EXIT_SUCCESS);
    }


    /* On success: The child process becomes session leader */
    

    // signal(SIGCHLD, SIG_IGN);
    // signal(SIGHUP, SIG_IGN);
    sleep(3);
    /* Fork off for the second time*/
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);


    /* Success: Let the parent terminate */
    if (pid > 0){
        printf("The child becomes parent and spawns it's own child.\n");
        sleep(3);
        exit(EXIT_SUCCESS);
        printf("Parent dies. Child is orphan.\n");
    }



    if (setsid() < 0)
        exit(EXIT_FAILURE);
    // prctl(PR_SET_CHILD_SUBREAPER);
    printf("Demon has spawned!\n");

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
    openlog ("FirstDemon", LOG_PID, LOG_DAEMON);
}

int main()
{
    skeleton_daemon();

    while (1)
    {
        //TODO: Insert daemon code here.
        syslog (LOG_NOTICE, "First daemon started.");
        sleep (20);
        break;
    }

    syslog (LOG_NOTICE, "First daemon terminated.");
    closelog();

    return EXIT_SUCCESS;
}