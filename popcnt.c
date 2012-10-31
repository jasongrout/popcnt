#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "timer.h"

#define MAX_NUM 10000

#ifdef POPCOUNT
#define POP popcnt[i] = __builtin_popcount(values[i])
#endif

#ifdef LOOKUP
#define POP popcnt[i] = popcnt_lookup[values[i] >> 8] + popcnt_lookup[values[i] & 0x00FF]
#endif

int main(int argc, char **argv) {
  uint8_t popcnt_lookup[256];
  uint16_t values[MAX_NUM];
  uint8_t popcnt[MAX_NUM];
  uint32_t i, j;
  uint64_t t;
  uint64_t sum = 0;
  uint64_t time = 0;

  srandom(0);
  for(i=0; i<MAX_NUM; i++) {
    values[i] = random() & 0xFFFF;
  }
  for(i=0; i<256; i++) {
    popcnt_lookup[i] = __builtin_popcount(i);
  }

  for(j=0; j<100; j++) {

    timer(&t); // initialize timer
    for(i=0; i<MAX_NUM; i++) {
      POP;
    }
    time += timer(&t);

    for(i=0; i<MAX_NUM; i++) {
      // we need to use popcnt so that the compiler doesn't optimize it away
      sum += popcnt[i];
    }
  }
  printf("Time: %0.3f ms\n", time/1000.0);
  printf("Hash: %llu\n", sum);
  return 0;
}
