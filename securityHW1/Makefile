CC=gcc
CFLAGS=-O2 -Wextra -Wall -Wno-unused-result -std=c99 -g
TARGET=GenTable.exe doCrack.exe
OBJS=GenTable.o doCrack.o

.PHONY: all clean

all: $(TARGET) 

GenTable.exe: $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^
	
doCrack.exe: $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $^
   
clean: 
	rm *.o $(TARGET)