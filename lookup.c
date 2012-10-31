#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "timer.h"

#define MAX_NUM 10000

int main(int argc, char **argv) {
  uint8_t popcnt_lookup[256];
  uint16_t values[MAX_NUM];
  uint8_t popcnt[MAX_NUM];
  uint32_t i, j;
  uint64_t t;

  for(i=0; i<256; i++) {
    popcnt_lookup[i] = __builtin_popcount(i);
  }

  srandom(0);
  for(i=0; i<MAX_NUM; i++) {
    values[i] = random() & 0xFFFF;
  }

  timer(&t); // initialize timer
  for(j=0; j<100; j++) {
    for(i=0; i<MAX_NUM; i++) {
      popcnt[i] = popcnt_lookup[values[i] >> 8] + popcnt_lookup[values[i] & 0x00FF];
    }
  }
  printf("Time: %0.3f ms\n", timer(&t)/1000.0);
  return 0;
}

