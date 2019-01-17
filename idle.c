#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>



int main(int argc, char const *argv[])
{
	printf("Staying idle...\n");
	pid_t pid = fork();
	if(pid == 0){
		/*while(1){
			printf("Alive\n");
			sleep(3);
		}*/
		sleep(5);
		printf("Ded.\n");
		return 0;
	}
	// pid_t pd = waitpid(pid, NULL, WNOWAIT);
	// siginfo_t pd;
	// waitid(P_ALL, -1, &pd, WNOWAIT);
	// printf("pd: %d\n", pd);
	// printf("pd: %d\n", pd.si_pid);
	// getchar();
	return 0;
}