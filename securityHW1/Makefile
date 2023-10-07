CC=gcc
CFLAGS=-O2 -Wextra -Wall -Wno-unused-result -std=c99 -g
TARGET=genTable.exe doCrack.exe
OBJS=genTable.o doCrack.o

.PHONY: all clean

all: $(TARGET) 

genTable.exe: $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^
	
doCrack.exe: $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $^
   
clean: 
	rm *.o $(TARGET)