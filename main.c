#include <stdio.h>
#include <stdlib.h>
#include "../BBBIOlib/BBBio_lib/BBBiolib.h"
#include <time.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0

char endThread = FALSE;
double loop_time_count = 0;
double loop_time_mean = 0;
double inner_loop_time = 0;

void *readerThread(void *vargp){
  int last_state = FALSE;
  while(!endThread) {
    clock_t init_loop_time = clock();
    int test_state = is_high(8,11);
    if(test_state != last_state) {
      // printf("State changed to %s\n", test_state ? "true" : "false");
    }
    last_state = test_state;
    clock_t elapsed = clock() - init_loop_time;
    double time_in_seconds = ((double)elapsed)/CLOCKS_PER_SEC;
    // should sleep to fulfill 1usec clock
    unsigned int time_in_nano = time_in_seconds*1000000000;
    inner_loop_time = time_in_seconds;
    if(time_in_nano < 1000){
      struct timespec req, rem;
      req.tv_sec = 0;
      req.tv_nsec = 1000 - time_in_nano;
      nanosleep(&req, &rem);
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
  iolib_setdir(8, 11, BBBIO_DIR_IN);

  pthread_t readerThreadId;
  pthread_create(&readerThreadId, NULL, readerThread, &readerThreadId);

  struct timespec req, rem;
  req.tv_sec = 10;
  req.tv_nsec = 0;
  nanosleep(&req, &rem);

  endThread = TRUE;
  pthread_join(readerThreadId, NULL);

  printf("loops %d\n", loop_time_count);
  printf("mean time in micro %f\n", loop_time_mean*1000000);
  printf("%f\n", inner_loop_time);

  iolib_free();
  return(0);
}
