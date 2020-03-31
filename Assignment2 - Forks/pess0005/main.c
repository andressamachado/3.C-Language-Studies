#include <signal.h>
#include <unistd.h>
#include <stdio.h>  // sdterr, stdin, printf, fscanf
#include <stdlib.h> // exit
#include "parse.h"
#include "parent.h"
#include "child.h"

/* PROGRAM: Guessing Game
   AUTHORS: Andressa Machado [040923007]
   DATE: 19.April.2019
   PURPOSE: A program to simulate a guessing game with two parallel processes.
   LEVEL OF DIFFICULTY: 7
   CHALLENGES: problems to work with parsing
   HOURS SPENT: 6 hours
*/

int forkWithPipes(int *pfdRead, int *pfdWrite);

int main(int argc, char *argv[]) {
  // Options
  // Handle the command line arguments

  // parse command line before forking

  // Default range and timeout
  short timeout = 10;
  short range = 100;
  parseArguments(argc, argv, &range, &timeout);


  // First forking with pipes
  int fdRead;
  int fdWrite;
  int pid = forkWithPipes(&fdRead, &fdWrite);

  // registering signal handlers
  signal(SIGUSR1, endProgramHandler);
  signal(SIGUSR2, mySignalHandler);

  // if forks failed, exit
  if (pid == -1) {
    printf("There was an error forking the processes, exiting");
    exit(1);
  }
  // Testing first message sending
  if (pid != 0) { /* …. am I the parent? */
    main_parent(fdRead, fdWrite, range, timeout);
  } else { /* … I must be the child! */
    main_child(fdRead, fdWrite, range, timeout);
  }

  // closing pipes
  close(fdRead);
  close(fdWrite);
}

int forkWithPipes(int *pfdRead, int *pfdWrite) {
  static int pipeFDs_C2P[2];
  pipe(pipeFDs_C2P);
  static int pipeFDs_P2C[2];
  pipe(pipeFDs_P2C);

  int pid = fork();

  if (pid != 0) { // Parent
    close(pipeFDs_P2C[0]);
    close(pipeFDs_C2P[1]);
    *pfdWrite = pipeFDs_P2C[1];
    *pfdRead = pipeFDs_C2P[0];
  } else { // Childs
    close(pipeFDs_P2C[1]);
    close(pipeFDs_C2P[0]);
    *pfdWrite = pipeFDs_C2P[1];
    *pfdRead = pipeFDs_P2C[0];
  }
  return pid;
}
