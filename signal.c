/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int handlerInvoked = 0;

void handler(int signum)
{ //signal handler
  printf("Hello World!\n");
  handlerInvoked = 1; //signal was recieved and handler was invoked
  // exit(1); //exit after printing
}

int main(int argc, char * argv[])
{
  signal(SIGALRM,handler); //register handler to handle SIGALRM
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