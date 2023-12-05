CC=gcc
CFLAGS=-O2 -Wextra -Wall -Wno-unused-result -std=c99 -g
TARGET=bfCrack
OBJS1=bfCrack.o

.PHONY: all clean

all: $(TARGET) 

bfCrack: $(OBJS1) 
	$(CC) $(CFLAGS) -o $@ $^
	
%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $^
   
clean: 
	rm *.o $(TARGET)