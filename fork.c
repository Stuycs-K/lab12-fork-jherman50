#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>

int err(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}

int randomInt(randfile) {
	int t;
		int *randint;
		read(randfile, randint, 4);
	  t = abs(*randint) % 5;
		return t;
}

int main() {
	int randfile;
	randfile = open("/dev/random", O_RDONLY, 0);
	if(randfile == -1) {
			err();
	}
	pid_t p, q;
	printf("%d about to create 2 child processes\n", getpid());
	p = fork();
	if(p<0){
		perror("fork fail");
		exit(1);
	} else if (p == 0){
		int s = randomInt(randfile);
		printf("%d %dsec\n", getpid(), s);
		sleep(s);
		printf("%d finished after %d seconds\n", getpid(), s);
	} else{
		q = fork();
		int s = randomInt(randfile);
		printf("%d %dsec\n", getpid(), s);
		sleep(s);
		printf("%d finished after %d seconds\n", getpid(), s);
  }
  return 0;
}
