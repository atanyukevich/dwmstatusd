#-----------------------------------------------------------------------------#
#CHOST=x86_64-pc-linux-gnu
CC=${CHOST}-gcc
CFLAGS=-O2 -pipe -march=core2 -Wall -pedantic -D_GNU_SOURCE
#CFLAGS+=-D_DEBUG
SOURCES=getbat.c gettime.c smprintf.c gettemperature.c pulseaudiovol.c cpufreq.c main.c
OBJECTS=$(SOURCES:.c=.o)
#-----------------------------------------------------------------------------#

all: mystat 

mystat: $(OBJECTS) cpufreq.o main.o
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ -lX11 -lpulse

clean:
	rm -fv *.o mystat 
#-----------------------------------------------------------------------------#
