CC = gcc
CFLAGS = -g3 -Wall -O3 -std=c99 -fsanitize=address

SOURCES = main.c node.c block.c sync.c
HEADERS = block_chain.h
OBJECTS = $(SOURCES:.c=.o)
TARGET = my_blockchain

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $(TARGET)

.PHONY: clean

clean:
	@rm -f $(OBJECTS) $(TARGET) core
