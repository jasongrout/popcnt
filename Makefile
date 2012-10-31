CC = cc
COPT = -O3 -msse4.2

all: popcnt lookup

popcnt: popcnt.c timer.h
	$(CC) $(COPT) -DPOPCOUNT popcnt.c -o popcnt

lookup: popcnt.c timer.h
	$(CC) $(COPT) -DLOOKUP popcnt.c -o lookup

asm: popcnt.c timer.h
	$(CC) -S $(COPT) -DPOPCOUNT popcnt.c -o popcnt.asm
	$(CC) -S $(COPT) -DLOOKUP  popcnt.c -o lookup.asm