CC = cc

COPT = -O3 -msse4.2
COPT = -S -msse4.2 # assembly

all: popcnt lookup

popcnt: popcnt.c timer.h
	$(CC) $(COPT) popcnt.c -o popcnt

lookup: lookup.c timer.h
	$(CC) $(COPT) lookup.c -o lookup
