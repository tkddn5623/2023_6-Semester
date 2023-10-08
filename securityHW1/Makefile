CC=gcc
CFLAGS=-O2 -Wextra -Wall -Wno-unused-result -std=c99 -g
TARGET=genTable doCrack
OBJS1=genTable.o reduction.o aes.o 
OBJS2=doCrack.o reduction.o aes.o

.PHONY: all clean

all: $(TARGET) 

genTable: $(OBJS1) 
	$(CC) $(CFLAGS) -o $@ $^
	
doCrack: $(OBJS2) 
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $^
   
clean: 
	rm *.o $(TARGET)