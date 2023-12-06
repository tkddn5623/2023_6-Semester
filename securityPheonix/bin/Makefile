CC=gcc
CFLAGS=-Wextra -Wall -Wno-unused-result -std=c99
TARGET=binary
OBJS=$(TARGET).o

.PHONY: all clean

all: $(TARGET) 

$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $^
   
clean: 
	rm *.o $(TARGET)