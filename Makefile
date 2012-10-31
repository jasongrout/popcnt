CC = cc
COPT = -O3 -msse4.2

all: popcnt lookup

popcnt: popcnt.c timer.h
	$(CC) $(COPT) popcnt.c -o popcnt

lookup: lookup.c timer.h
	$(CC) $(COPT) lookup.c -o lookup

asm: popcnt.c lookup.c timer.h
	$(CC) -S $(COPT) popcnt.c -o popcnt.asm
	$(CC) -S $(COPT) lookup.c -o lookup.asm