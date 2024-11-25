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

int randomInt() {
    int randfile;
    int randint;
    randfile = open("/dev/random", O_RDONLY, 0);
    if(randfile == -1) {
        err();
    }
    return randint;
}

int main() {
  printf("im in main\n");
  pid_t p, q;
  printf("%d about to create 2 child processes\n", getpid());
  p = fork();
  if(p<0){
    perror("fork fail");
    exit(1);
  } else if (p == 0){
    printf("%d %dsec\n", getpid(), randomInt());
    q = fork();
    printf("%d %dsec\n", getpid(), randomInt());
    printf("Hello from Child!\n");
  }else{
    printf("Hello from Parent!\n");
  }
  return 0;
}
