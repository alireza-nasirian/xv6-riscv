#include "kernel/types.h"
#include "user/user.h"
#include "../kernel/sysinfo.h"

int main(void)
{
  struct sysinfo sysi;
  int pid;

  sysinfo(&sysi);
  printf("-totalram = %d KB\t-freeram = %d KB\n", sysi.totalram / 1000, sysi.freeram / 1000);

  printf("calling sbrk()\n");
  sbrk(sysi.freeram * 2 / 3);
  
  sysinfo(&sysi);
  printf("-totalram = %d KB\t-freeram = %d KB\n", sysi.totalram / 1000, sysi.freeram / 1000);

  pid = fork();
  if (pid > 0){
    wait(0);
    printf("this is the parent process!\n");
  }
  else if(pid == 0)
    printf("this is the child process!\n");
  else
    printf("ERR: fork failed");
  
  exit(0);
}
