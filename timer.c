/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

int handlerInvoked = 0;
int alarms = 0; //counter to store the number of alarms 
time_t start_time;

// void handler(int signum)
// { //signal handler
//   printf("Hello World!\n");
//   handlerInvoked = 1; //signal was recieved and handler was invoked
//   // exit(1); //exit after printing
// }

void alarmHandler(int signum){
  printf("Hello World!\n");
  handlerInvoked = 1;
  alarms++;
}

void ctrlcHandler(int signum){
  time_t end_time = time(NULL);
  time_t total_time = end_time - start_time;
  printf("Total number of alarms delivered: %d\n", alarms);
  printf("Total execution time: %d seconds\n", alarms);
  exit(0);
}

int main(int argc, char * argv[])
{
  signal(SIGALRM,alarmHandler); //register handler to handle SIGALRM
  signal(SIGINT, ctrlcHandler);
  alarm(1); //Schedule a SIGALRM for 1 second
  // while(1); //busy wait for signal to be delivered
  // return 0; //never reached
  while(1){
    while (!handlerInvoked){}
    printf("Turing was right!\n");

    //reset the signal to 0
    handlerInvoked = 0;
    //schedule the next SIGALRM for 1 second
    alarm(1);
  }

  return 0;

}