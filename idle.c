#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <signal.h>



int main(int argc, char const *argv[])
{
	printf("Staying idle...\n");
	pid_t pid = fork();
	if(pid == 0){
		/*while(1){
			printf("Alive\n");
			sleep(3);
		}*/
		sleep(10);
		return 0;
	}
	return 0;
}