
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
            sync_blockchain(*super_node);
            break;

        case LS_CMD:
            printNode(*super_node, true);
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
    char *bid = my_str_from_str(buff, 10);
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
            free(bid);
        }
        else if (node_id == -1)
        {
            // Add block to all nodes
            struct blockchain_Node *node = *super_node;
            while (node != NULL)
            {
                // Check if block is already there in Node
                char *bid_copy = my_str_copy(bid);
                const int block_id_added = addBlock(*super_node, node->nid, bid_copy);
                if (block_id_added == BLOCK_EXISTS)
                {
                    callErrorThree();
                    free(bid_copy);
                }
                else if (block_id_added == NODE_NOT_EXIST)
                {
                    callErrorFour();
                    free(bid_copy);
                }
                else
                {
                    // Do nothing
                }
                node = node->next;
            }
            free(bid);
        }
        else
        {
            // Check if block is already there in Node
            const int block_id_added = addBlock(*super_node, node_id, bid);
            if (block_id_added == BLOCK_EXISTS)
            {
                callErrorThree();
                free(bid);
            }
            else if (block_id_added == NODE_NOT_EXIST)
            {
                callErrorFour();
                free(bid);
            }
            else
            {
                // Do nothing
            }
        }
    }
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
        deleteAllNodes(*super_node);
        *super_node = NULL;
    }
    else
    {
        // Check if node_id exists
        struct blockchain_Node *node_exists = search_for_a_node(*super_node, node_id);
        
        if (node_exists != NULL)
        {
            // Remove node with node _id
            *super_node = deleteNode(*super_node, node_id);
        }
        else
        {
            callErrorFour();
        }
    }
}

void my_handle_rm_block(const char *buff, struct blockchain_Node **super_node)
{
    char *bid = my_str_from_str(buff, 9);
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
        else if (blockExists(*super_node, bid) == true)
        {
            // Remove bid from all nodes
            deleteBlock(*super_node, bid);
        }
        else
        {
            callErrorFive();
        }
        free(bid);
    }
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



