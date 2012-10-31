#include <sys/time.h>

uint64_t timer(uint64_t *t) {
  struct timeval curr_time;
  struct timezone tz;
  uint64_t old_time;

  old_time = *t;
  gettimeofday(&curr_time, &tz);
  *t = curr_time.tv_sec * 1000000 + curr_time.tv_usec;
  return *t - old_time;
}
