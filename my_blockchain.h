
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BID_SIZE 10;

#define BREAK_READING 1
#define CONTINUE_READING 0

#define MAX_READ_SIZE 512

struct blockchain_Node {
    int nid;
    // int bid_size;
    // char** bid_array;
    struct blockchain_Node *next;
} blockchain;

struct blockchain_Node* createNode(int nid_numb);
void addNode(struct blockchain_Node *node, int nid);

struct blockchain_Node* search_for_a_node(struct blockchain_Node *node, int nid_numb);
struct blockchain_Node* deleteNode(struct blockchain_Node *node, int nid_numb);

int get_blockchain_size(struct blockchain_Node *node);

int addBid(struct blockchain_Node *node, int nid_numb, char* bid_string);
int rmBid(struct blockchain_Node *node, char* bid_string);

void callErrorOne();
void callErrorTwo();
void callErrorThree();
void callErrorFour();
void callErrorFive();
void callErrorSix();

void printNode(struct blockchain_Node *node, const bool print_blocks);
void freeNodes(struct blockchain_Node *node);

int my_str_len(const char *str);
int my_str_write(const int fd, const char *str);
int my_int_write(const int fd, const int input);
int my_prompt_write(const int fd, const bool is_sync, const int node_size);
bool my_str_compare(const char *left, const char *right);
bool my_str_n_compare(const char *left, const char *right, const int len);
bool my_str_nn_compare(const char *left, const char *right, const int start_ind, const int len);

int my_prompt_handle(const int fd, struct blockchain_Node **super_node);
int my_str_to_int(const char *str, const int start_ind);
char *my_str_from_str(const char *str, const int start_ind);

