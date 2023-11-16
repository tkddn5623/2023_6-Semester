CC=gcc
CFLAGS=-O2 -Wextra -Wall -Wno-unused-result -std=c99 -fno-stack-protector -z execstack
TARGET=bof_func_c
OBJS=bof_func_c.o

.PHONY: all clean

all: $(TARGET) 

bof_func: $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $^
   
clean: 
	rm *.o $(TARGET)