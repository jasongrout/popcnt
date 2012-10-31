CC = cc
CFLAGS = -O3 -msse4.2

all: popcnt lookup

popcnt: popcnt.c timer.h
	$(CC) $(CFLAGS) -DPOPCOUNT popcnt.c -o $@

lookup: popcnt.c timer.h
	$(CC) $(CFLAGS) -DLOOKUP popcnt.c -o $@

asm: popcnt.asm lookup.asm

popcnt.asm: popcnt.c timer.h
	$(CC) -S $(CFLAGS) -DPOPCOUNT popcnt.c -o $@

lookup.asm: popcnt.c timer.h
	$(CC) -S $(CFLAGS) -DLOOKUP  popcnt.c -o $@