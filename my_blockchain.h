
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

// #define READLINE_READ_SIZE 2

// static struct Storage **big_storage = NULL; ///< Global static linked list variable to hold all read lines of characters from file description

/// @brief Structure to hold Block info
struct Block
{
    char *id;
};

/// @brief Structure to hold Node info
struct Node
{
    int id;
    struct Block block;
};

/// @brief Structure to handle chain of nodes
struct BlockChain
{
    struct Node;
    struct BlockChain* next;
};

struct Block createBlock(char *id);
struct Node createNode(int id);
struct BlockChain *createBlockChain(struct Node node);
void addBlockChain(struct BlockChain *head, struct Node node);
void freeBlockChain(struct BlockChain *head);

/// @brief Function to create BlockChain 
/// @param data Data the storage is created with
/// @return Pointer to the storage created
// struct Storage *createStorage(char *data);

// /// @brief Function to add storage into linked list
// /// @param head Pointer to head of the list
// /// @param data Data out of which storage is created and appended to the end of the linked list
// void addStorage(struct Storage *head, char *data);

// /// @brief Function to free out allocated memory from heap
// /// @param storage Data to free out
// void freeStorage(struct Storage **storage);

// /// @brief Function to check if all characters in buffer is zero or not
// /// @param buff Buffer to check for characters
// /// @return True if all are zeros
// bool isAllZeros(char *buff);

// /// @brief Main readling function
// /// @param fd File description
// /// @return String in the same line
// char* myReadline(int fd);