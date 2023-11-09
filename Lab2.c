#include  <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include  <sys/types.h>

int main(){

  pid_t child1, child2;
  int max_loops = 30;

  //seed the random number generator
  srandom(time(NULL));

  //create the first child process
  child1 = fork();

  //check for any errors with the fork
  if (child1 < 0){
    perror("Fork failed.");
    exit(1);
  }

  //find the parent process
  if (child1 > 0){
    printf("This is the parent process. pid = %d\n", getpid());
    

    //create the second child process
    child2 = fork();

    //check for any errors with the fork
    if (child2 < 0){
      perror("Fork failed.");
      exit(1);
    }

    if (child2 > 0){
      int status1, status2;

      //wait for both process to complete
      wait(&status1);
      wait(&status2);

      printf("Child Pid: %d has completed\n", getpid());
      printf("Child Pid: %d has completed\n", getpid());
    }

    // //wait for child processes to terminate
    // waitpid(child1, &status, 0);
    // printf("Child 1 has terminated.\n");
    // waitpid(child2, &status, 0);
    // printf("Child 2 has terminated.\n");
  }

  //first child process
  if (child1 == 0){
    printf("First child process. pid = %d\n", getpid());

    //random number of loop iterations
    int loops = random() % max_loops + 1;

    int i;
    for (i=0; i < loops; i++){
      printf("Child Pid: %d is going to sleep!\n", getpid());
      //sleep for a random amount of time (but no more than 10s)
      sleep(random() % 10 +1);
      printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
    }

    //terminate the first child process
    exit(0);
  }

  // //create the second child process
  // child2 = fork();

  // //check for any errors with the fork
  // if (child2 < 0){
  //   perror("Fork failed.");
  //   exit(1);
  // }

  // //find the parent process
  // if (child2 > 0){
  //   printf("This is the parent process. pid = %d", getpid());
  // }

  //second child process
  if (child2 == 0){
    printf("Second child process. pid = %d\n", getpid());

    //random number of loop iterations
    int loops = random() % max_loops + 1;

    int i;
    for (i=0; i < loops; i++){
      printf("Child Pid: %d is going to sleep!\n", getpid());
      //sleep for a random amount of time (but no more than 10s)
      sleep(random() % 10 +1);
      printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
    }

    //terminate the second child process
    exit(0);
  }

  return 0;
}