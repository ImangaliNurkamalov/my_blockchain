
#include "../include/my_blockchain.h"
#include "../include/error_msgs.h"
#include "../include/helpers.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int my_prompt_write(const int fd, const bool is_sync, const int node_size)
{
    int sum_chars_printed = 0;
    int chars_printed = my_str_write(1, "[");
    if (chars_printed < 0)
    {
        return -1;
    }
    else
    {
        sum_chars_printed += chars_printed;
    }
    
    chars_printed = (is_sync == true) ? my_str_write(1, "s") : my_str_write(1, "-");
    if (chars_printed < 0)
    {
        return -1;
    }
    else
    {
        sum_chars_printed += chars_printed;
    }
    
    chars_printed = my_int_write(1, node_size);
    if (chars_printed < 0)
    {   
        return -1;
    }
    else
    {
        sum_chars_printed += chars_printed;
    }
    
    chars_printed = my_str_write(1, "]> ");
    if (chars_printed < 0)
    {
        return -1;
    }
    else
    {
        sum_chars_printed += chars_printed;
    }

    return sum_chars_printed;
}

int my_prompt_handle(const int fd, struct blockchain_Node **super_node)
{
    char buff[MAX_READ_SIZE];
    if (my_read_from_console(fd, buff) < 0)
    {
        return CONTINUE_READING;
    }

    const int cmd_given = my_blockchain_command(buff);
    switch (cmd_given)
    {
        case ADD_NODE_CMD:
            my_handle_add_node(buff, super_node);
            break;

        case ADD_BLOCK_CMD:
            my_handle_add_block(buff, super_node);
            break;
        
        case RM_NODE_CMD:
            my_handle_rm_node(buff, super_node);
            break;

        case RM_BLOCK_CMD:
            my_handle_rm_block(buff, super_node);
            break;

        case SYNC_CMD:
            printf("Syncing!\n");
            // Call sync function
            break;

        case LS_CMD:
            printNode(*super_node, false);
            break;

        case QUIT_CMD:
            return BREAK_READING;
            break;
        
        case UNKNOWN_CMD:
            callErrorSix();
            break;

        default:
            callErrorSix();
            break;
    }

    return CONTINUE_READING;
}

void my_handle_add_node(const char *buff, struct blockchain_Node **super_node)
{
    const int node_id = my_str_to_int(buff, 9);

    if (node_id < 0)
    {
        callErrorSix();
    }
    else
    {
        // Add node with node_id
        if (*super_node == NULL)
        {
            *super_node = createNode(node_id);
        }
        else if (search_for_a_node(*super_node, node_id) != NULL)
        {
            callErrorTwo();
        }
        else
        {
            addNode(*super_node, node_id);
        }
    }
}

void my_handle_add_block(const char *buff, struct blockchain_Node **super_node)
{
    const char *bid = my_str_from_str(buff, 10);
    if (bid == NULL)
    {
        callErrorSix();
    }
    else
    {
        const int bid_len = my_str_len(bid);
        const int node_id = my_str_to_int(buff, 10 + bid_len + 1);

        if (node_id < -1)
        {
            callErrorSix();
        }
        else if (node_id == -1)
        {
            // Add block to all nodes
        }
        else
        {
            // Add bid into node_id
            struct blockchain_Node *node = search_for_a_node(*super_node, node_id);
            if (node == NULL)
            {
                callErrorFour();
            }
            else
            {
                // Check if block is already there in Node
                addBlock(*super_node, node_id, (char *)bid);
            }
        }
    }

    // Temporary
    free((char *)bid);
}

void my_handle_rm_node(const char *buff, struct blockchain_Node **super_node)
{
    const int node_id = my_str_to_int(buff, 8);
    if (node_id < -1)
    {
        callErrorSix();
    }
    else if (node_id == -1)
    {
        freeNodes(*super_node);
        *super_node = NULL;
    }
    else
    {
        // Remove node with node _id
    }
}

void my_handle_rm_block(const char *buff, struct blockchain_Node **super_node)
{
    const char *bid = my_str_from_str(buff, 9);
    if (bid == NULL)
    {
        callErrorSix();
    }
    else
    {
        const int bid_len = my_str_len(bid);
        const int str_full_len = my_str_len(buff) - 1;

        if ((bid_len + 9) != str_full_len)
        {
            callErrorSix();
        }
        else
        {
            // Remove bid from all nodes
        }
    }

    // Temporary
    free((char *)bid);
}

int my_read_from_console(const int fd, char *buff)
{
    for (int i = 0; i < MAX_READ_SIZE; ++i)
    {
        buff[i] = 0;
    }
    const int read_sz = read(fd, buff, MAX_READ_SIZE);
    if (read_sz < 2)
    {
        callErrorSix();
        return -1;
    }
    return 0;
}

int my_blockchain_command(const char *buff)
{
    if (my_str_nn_compare(buff, "add node", 0, 8) == true)
    {
        return ADD_NODE_CMD;
    }
    else if (my_str_nn_compare(buff, "add block", 0, 9) == true)
    {
        return ADD_BLOCK_CMD;
    }
    else if (my_str_nn_compare(buff, "rm node", 0, 7) == true)
    {
        return RM_NODE_CMD;
    }
    else if (my_str_nn_compare(buff, "rm block", 0, 8) == true)
    {
        return RM_BLOCK_CMD;
    }
    else if (my_str_nn_compare(buff, "sync", 0, 4) == true)
    {
        return SYNC_CMD;
    }
    else if (my_str_nn_compare(buff, "ls", 0, 2) == true)
    {
        return LS_CMD;
    }
    else if (my_str_nn_compare(buff, "quit", 0, 4) == true)
    {
        return QUIT_CMD;
    }
    else
    {
        return UNKNOWN_CMD;
    }
}

int my_str_to_int(const char *str, const int start_ind)
{
    // Subtracting '\n' (pressing enter creates new line)
    const int str_len = my_str_len(str) - 1;

    if ((str_len - start_ind) == 1 && str[start_ind] == '*')
    {
        return -1;
    }
    else if (str_len <= start_ind)
    {
        return -2;
    }
    else
    {
        const int end_ind = str_len;

        // Sanity check, the rest should be integer
        for (int i = start_ind; i < end_ind; ++i)
        {
            if (str[i] < 48 || str[i] > 57)
            {
                return -2;
            }
        }

        int ret_int = 0;
        for (int i = start_ind; i < end_ind; ++i)
        {
            int len = end_ind - i;
            int pow_10 = 1;
            while (len > 1)
            {
                pow_10 *= 10;
                --len;
            }

            ret_int += (str[i] - 48) * pow_10;
        }
        return ret_int;
    }
}

char *my_str_from_str(const char *str, const int start_ind)
{
    // Subtracting '\n' (pressing enter creates new line)
    const int str_len = my_str_len(str) - 1;

    char *str_ret = NULL;
    int str_ret_len = 0;
    
    if (str_len < start_ind)
    {
        return str_ret;
    }
    else
    {
        const int end_ind = str_len;

        // Get the length of str up until space or end
        for (int i = start_ind; i < end_ind; ++i)
        {
            if (str[i] != ' ')
            {
                ++str_ret_len;
            }
            else
            {
                break;
            }
        }
        
        if (str_ret_len == 0)
        {
            return str_ret;
        }
        else
        {
            str_ret = (char *) malloc ((str_ret_len + 1) * sizeof(char));
        }        
        
        for (int i = start_ind; i < str_ret_len + start_ind; ++i)
        {
            str_ret[i - start_ind] = str[i];
        }
        str_ret[str_ret_len] = 0;
        return str_ret;
    }
}
















void printNode(struct blockchain_Node *node, const bool print_blocks)
{
    struct blockchain_Node *head = node;
    while (head != NULL)
    {
        my_int_write(1, head->nid);
        
        if (print_blocks == true)
        {
            struct blocks *curr_block = head->bidList->head;
            while(curr_block != NULL)
            {
                if (curr_block == head->bidList->head)
                {
                    my_str_write(1, ": ");
                }

                my_str_write(1, curr_block->block_data);
                
                if (curr_block->next_block != NULL)
                {
                    my_str_write(1, ", ");
                }
            }
        }

        my_str_write(1, "\n");
        head = head->next;
    }
}

void freeNodes(struct blockchain_Node *node)
{
    struct blockchain_Node *temp, *head = node;
    while(head != NULL)
    {
        temp = head;
        head = head->next;
        temp->next = NULL;
        free(temp);
    }
}

struct blockchain_Node* search_for_a_node(struct blockchain_Node *node, int nid_numb)
{
    struct blockchain_Node* current = node; 
    while(current) 
    {
        if(nid_numb == current->nid) 
        {
            return current;
        }
        current = current->next;
    }
    return current; 
}

int get_blockchain_size(struct blockchain_Node *node)
{
    int count = 0;
    while(node != NULL)
    {
        ++count;
        node = node->next;
    }
    return count;
}

