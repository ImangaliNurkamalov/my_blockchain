#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BLOCK_ADDED    1
#define BLOCK_EXISTS   2
#define NODE_NOT_EXIST 3
#define NODE_DELETED   4

struct blockList {
    struct blocks *head;
    struct blocks *tail;
};

struct blocks {
    char* block_data;
    struct blocks *next_block;
};

struct blockchain_Node {
    int nid;
    int bid_array_size;
    struct blockList *bidList;
    bool sync;
    struct blockchain_Node *next;
};

struct blockchain_Node* createNode(int nid_numb);
void addNode(struct blockchain_Node *node, int nid);
struct blockchain_Node *deleteNode(struct blockchain_Node *node, int nid_numb);
void deleteAllNodes(struct blockchain_Node *fisrt_node);
void printNode(struct blockchain_Node *node, const bool print_blocks);
struct blockchain_Node* search_for_a_node(struct blockchain_Node *node, int nid_numb);
int get_blockchain_size(struct blockchain_Node *node);

struct blocks* createBlock(char* data);
int addBlock(struct blockchain_Node *node, int nid_numb, char* bid_string);
void deleteBlock(struct blockchain_Node *node, char* bid_string);
bool blockExists(struct blockchain_Node *node, char* bid_string);

void freeBlockChainNode(struct blockchain_Node *node);

char** collect_unique_blocks(struct blockchain_Node *node, int *block_numb);
void sync_blockchain(struct blockchain_Node *node);
bool is_in_sync(struct blockchain_Node *node);