#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// Programa de prueba para Lottery Scheduling
int
main(int argc, char *argv[])
{
  int pid;
  int tickets = 10;

  if(argc > 1){
    tickets = atoi(argv[1]); // si se pasa argumento, usa ese número de tickets
  }

  // asignar tickets al proceso actual
  settickets(tickets);

  printf("Proceso principal (PID %d) con %d tickets\n", getpid(), tickets);

  // crear 3 hijos con diferente cantidad de tickets
  for(int i = 0; i < 3; i++){
    pid = fork();
    if(pid == 0){ // hijo
      settickets(10 * (i+1)); // 10, 20, 30 tickets
      for(int j = 0; j < 100000000; j++){
        if(j % 20000000 == 0){
          int counter;
          getpinfo(&counter);
          printf("PID %d ejecutado %d veces\n", getpid(), counter);
        }
      }
      exit(0);
    }
  }

  // esperar a todos los hijos
  for(int i = 0; i < 3; i++)
    wait(0);

  printf("Prueba de Lottery Scheduling completada.\n");
  exit(0);
}

