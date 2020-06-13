CC = gcc
CFLAGS = -g3 -Wall -O3 -std=c99 -fsanitize=address

SOURCES = main.c node.c block.c sync.c src/my_blockchain.c src/helpers.c src/error_msgs.c
HEADERS = block_chain.h include/my_blockchain.h include/helpers.h include/error_msgs.h
OBJECTS = $(SOURCES:.c=.o)
TARGET = my_blockchain

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $(TARGET)

.PHONY: clean

clean:
	@rm -f $(OBJECTS) $(TARGET) core
