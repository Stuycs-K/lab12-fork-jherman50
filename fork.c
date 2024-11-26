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
#include <sys/wait.h>

int err(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}

int randomInt(int randfile) {
	int t;
	int *randint;
	read(randfile, randint, 4);
	t = abs(*randint) % 5 + 1;
	return t;
}

int main() {
	int randfile, x, y;
	randfile = open("/dev/random", O_RDONLY, 0);
	if(randfile == -1) {
			err();
	}
  x = randomInt(randfile);
  y = randomInt(randfile);
	pid_t p, q;
	printf("%d about to create 2 child processes\n", getpid());
	p = fork();
	if(p<0){
		perror("fork fail");
		exit(1);
	} else if (p == 0){
		printf("%d %dsec\n", getpid(), x);
		sleep(x);
		printf("%d finished after %d seconds\n", getpid(), x);
    exit(x);
	} else {
    q = fork();
    if (q == 0) {
      int y = randomInt(randfile);
  		printf("%d %dsec\n", getpid(), y);
  		sleep(y);
  		printf("%d finished after %d seconds\n", getpid(), y);
      exit(y);
    }
    else {
      int status;
      int w = wait(&status);
      if (WIFEXITED(status)) {
        printf("Main process %d is done. Child %d slept for %d sec\n", getpid(), w, WEXITSTATUS(status));
      }
    }
  }
  return 0;
}
