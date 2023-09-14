CC=gcc
CFLAGS=-O2 -Wextra -Wall -Wno-unused-result -std=c99 -g
TARGET=exercise.exe
OBJS=exercise.o

.PHONY: all clean

all: $(TARGET) 

exercise.exe: $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $^
   
clean: 
	rm *.o $(TARGET)