#include <stdio.h>
#include <stdlib.h>
#include "../BBBIOlib/BBBio_lib/BBBiolib.h"
#include <time.h>
#include <pthread.h>

char endThread = false;
double loop_time_count = 0;
double loop_time_mean = 0;

void *readerThread(void *vargp){
  char last_state = false;
  while(!endThread) {
    clock_t init_loop_time = clock();
    char test_state = is_high(8,8);
    if(test_state != last_state) {
      printf("State changed to %s", test_state ? "true" : "false");
      last_state = test_state;
    }
    clock_t elapsed = clock() - init_loop_time;
    double time_in_seconds = ((double)elapsed)/CLOCKS_PER_SEC;
    // should sleep to fulfill 1usec clock
    unsigned int time_in_nano = time_in_seconds*1000000000;
    if(time_in_nano < 1000){ 
      nanosleep(1000 - time_in_nano)
    }

    clock_t full_elapsed = clock() - init_loop_time;
    double full_time_in_seconds = ((double)full_elapsed)/CLOCKS_PER_SEC;
    double loop_time_sum = (loop_time_mean*loop_time_count + full_time_in_seconds);
    loop_time_count += 1;
    loop_time_mean = loop_time_sum / loop_time_count;
  }
  return NULL;
}

int main(void) {
  iolib_init();
  iolib_setdir(8, 8, BBBIO_DIR_IN);

  pthread_t readerThreadId;
  pthread_create(&readerThreadId, NULL, readerThread, &readerThreadId);

  sleep(10);
  
  endThread = true;
  pthread_join(readerThreadId, NULL);

  printf("%f\n", loop_time_mean);

  iolib_free();
  return(0);
}
