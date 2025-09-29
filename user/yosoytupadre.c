#include "kernel/types.h"
#include "user/user.h"

int
main(void) {
  int pid  = getpid();
  int ppid = getppid();

  printf("Mi PID=%d  PPID=%d\n", pid, ppid);
  printf("ancestor(0)=%d\n", getancestor(0));
  printf("ancestor(1)=%d\n", getancestor(1));
  printf("ancestor(2)=%d\n", getancestor(2));
  exit(0);
}
