#include <stdio.h>
#include <stdlib.h>
#include "../BBBIOlib/BBBio_lib/BBBiolib.h"
#include <time.h>

int main(void) {
  iolib_init();
  iolib_setdir(8, 8, BBBIO_DIR_IN);

  int count = 0;
  clock_t init_time = clock();
  double high_count = 0;
  while(count < 1000000) {
    if (is_high(8, 8)) {
      high_count++;
    }
    count++;
  }

  clock_t elapsed = clock() - init_time ;

  double time_taken = ((double)elapsed)/CLOCKS_PER_SEC;
  printf("%f\n", time_taken);

  iolib_free();
  return(0);
}
