#ifndef MY_BLOCKCHAIN_H
#define MY_BLOCKCHAIN_H

#include "../block_chain.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BID_SIZE 10

#define BREAK_READING 1
#define CONTINUE_READING 2

#define ADD_NODE_CMD 1
#define ADD_BLOCK_CMD 2
#define RM_NODE_CMD 3
#define RM_BLOCK_CMD 4
#define LS_CMD 5
#define SYNC_CMD 6
#define QUIT_CMD 7
#define UNKNOWN_CMD 8

#define MAX_READ_SIZE 512

void my_blockchain(struct blockchain_Node **super_node);

int my_prompt_write(const int fd, const bool is_sync, const int node_size);

int my_prompt_handle(const int fd, struct blockchain_Node **super_node);
int my_blockchain_command(const char *str);
int my_read_from_console(const int fd, char *buff);

void my_handle_add_node(const char *buff, struct blockchain_Node **super_node);
void my_handle_add_block(const char *buff, struct blockchain_Node **super_node);
void my_handle_rm_node(const char *buff, struct blockchain_Node **super_node);
void my_handle_rm_block(const char *buff, struct blockchain_Node **super_node);
bool my_handle_print_block(const char *buff, struct blockchain_Node **super_node);

int my_str_to_int(const char *str, const int start_ind);
char *my_str_from_str(const char *str, const int start_ind);

#endif // MY_BLOCKCHAIN_H