Popcounts
=========

Consider an array of 10,000 16-bit integers.  Our goal is to get a corresponding array of 10,000 popcounts, one for each integer.

Recently someone claimed to me that the following strategy was a good one: create an 8-bit lookup table of all popcounts for integers less than 256.  Then for each 16-bit integer, look up how many bits are set in the upper 8 bits and the lower 8 bits and add the results together.  She was right---it is a good strategy.  Making the lookup table only 256 integers means that it can easily fit in L1 cache, so lookups are very fast.

However, if you have a hardware popcount instruction (e.g., some AMD chips, SSE 4.2, or some Itanium chips), it might be faster (or at least competitive) and simpler to just use the hardware popcount instruction to do the popcounts.  That is what we investigate here.

In this repository, we have two different approaches:

  * `make lookup` will generate `lookup`, a program that uses a simple lookup table strategy as described above.
  * `make popcnt` will generate `popcnt`, a program that uses a hardware popcount (if possible) and no lookup table.
  * `make asm` will generate the assembly listings for both programs so we can check to see if hardware popcounts were used

The timer has microsecond resolution, so we time the 10,000 popcounts 100 times (so 1,000,000 16-bit popcounts are done, and we only time the actual popcounts).  I verified that the hardware or software popcounts were used as noted below (do `make asm` to make the assembly files and search for `popcnt` in the assembly).

  * On a 2.4Ghz Intel i5 processor compiled with gcc 4.6.3 (OS X), using a *software* popcount, I get timings of around 6-9ms for the popcount strategy and 2.5-3.5ms for the lookup table strategy.  This is no huge surprise -- the software popcount is really doing a popcount of the entire 64-bit double word (using a smart strategy, of course), and the lookup table strategy is doing a simple 2-step popcount, with the lookup table probably in a cache very close to the CPU (like L1).
  * However, on an Intel i7 920 (2.67 Ghz) and gcc 4.4.3 (linux), using a *hardware* popcount, I get timings of around 1-1.8ms for the popcount strategy and 1.4-2.5ms for the lookup table strategy.  So we have a slight win for the hardware popcounts.
  * In order to check the difference on the i7 920, I also timed 10,000 popcounts 10,000 times.  The gap between the approaches widened: hardware popcounts were giving 107-112ms and lookup tables were giving 143-149ms.  Interestingly, the timings in this case and the previous case seemed to jump between the minimum and maximum values without a lot of timings in between.  This seemed a little odd.

So the take-away?  Investigate the capabilities of your platform when tuning.

