
#include "my_blockchain.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void callErrorOne()
{
    my_str_write(1, "No more resources available on the computer\n");
}

void callErrorTwo()
{
    my_str_write(1, "This node already exists\n");
}

void callErrorThree()
{
    my_str_write(1, "This block already exists\n");
}

void callErrorFour()
{
    my_str_write(1, "Node doesn't exist\n");
}

void callErrorFive()
{
    my_str_write(1, "Block doesn't exist\n");
}

void callErrorSix()
{
    my_str_write(1, "Command not found\n");
}

int my_str_len(const char *str)
{
    int count = 0;
    while(*str++ != 0)
    {
        ++count;
    }
    return count;
}

int my_str_write(const int fd, const char *str)
{
    return write(fd, str, my_str_len(str));
}

int my_int_write(const int fd, const int input)
{
    if (input < 0)
    {
        return -1;
    }
    else if (input == 0)
    {
        const int print_digit = 48;
        return write(fd, &print_digit, 1);
    }
    else
    {
        int count_chars_printed = 0;
        int len = 1;
        int temp = input;
        temp /= 10;
        while (temp > 0)
        {
            ++len;
            temp /= 10;
        }

        int print_digit = 48;
        while (len > 0)
        {
            int power_10 = 1;
            for (int j = 1; j < len; ++j)
            {
                power_10 *= 10;
            }

            print_digit = ( input / power_10 ) % 10 + 48;
            count_chars_printed += write(fd, &print_digit, 1);
            --len;
        }
        return count_chars_printed;
    }
}

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

bool my_str_compare(const char *left, const char *right)
{
    const int left_sz = my_str_len(left);
    const int right_sz = my_str_len(right);

    if (left_sz != right_sz)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < left_sz; ++i)
        {
            if (left[i] != right[i])
            {
                return false;
            }
        }
        return true;
    }
}

bool my_str_n_compare(const char *left, const char *right, const int len)
{
    const int left_sz = my_str_len(left);

    if (left_sz < len)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < len; ++i)
        {
            if (left[i] != right[i])
            {
                return false;
            }
        }
        return true;
    }
}

bool my_str_nn_compare(const char *left, const char *right, const int start_ind, const int len)
{
    const int left_sz = my_str_len(left);
    const int right_sz = my_str_len(right);

    if (len < 0)
    {
        return false;
    }
    else if (left_sz < start_ind + len)
    {
        return false;
    }
    else if (right_sz < len)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < len; ++i)
        {
            if (left[start_ind + i] != right[i])
            {
                return false;
            }
        }
        return true;
    }
}

struct prompt_t my_prompt_read(const int fd)
{
    char buff[512];
    const int read_sz = read(fd, &buff, 512);
    struct prompt_t ret;
    if (read_sz < 0)
    {
        ret.failure = true;
        return ret;
    }
    else
    {
        ret.failure = false;
    }

    ret.is_add_rm_cmd = false;
    ret.is_ls_cmd = false;
    ret.is_sync_cmd = false;

    struct add_rm_t add_rm_cmd;
    add_rm_cmd.action_t = (enum action)ADD;        
    add_rm_cmd.point_t = (enum point)NODE;
    add_rm_cmd.affected_t = (enum affected)ONE;
    add_rm_cmd.block_id = NULL;
    add_rm_cmd.node_id = 0;

    ret.add_rm_cmd = add_rm_cmd;

    enum affected affected_ls_cmd;
    affected_ls_cmd = (enum affected)ONE;

    ret.ls_affected = affected_ls_cmd;

    if (my_str_n_compare(buff, "add node", 8) == true)
    {
        printf("Adding node!\n");

        ret.is_add_rm_cmd = true;
        struct add_rm_t add_rm_cmd;

        add_rm_cmd.action_t = (enum action)ADD;        
        add_rm_cmd.point_t = (enum point)NODE;
        add_rm_cmd.block_id = NULL;
        add_rm_cmd.node_id = 0;

        ret.add_rm_cmd = add_rm_cmd;
    }
    else if (my_str_n_compare(buff, "rm node", 7) == true)
    {
        printf("Removing node!\n");

        ret.is_add_rm_cmd = true;
        struct add_rm_t add_rm_cmd;

        add_rm_cmd.action_t = (enum action)REMOVE;        
        add_rm_cmd.point_t = (enum point)NODE;
        add_rm_cmd.block_id = NULL;
        add_rm_cmd.node_id = 0;

        ret.add_rm_cmd = add_rm_cmd;
    }
    else if (my_str_n_compare(buff, "add block", 9) == true)
    {
        printf("Adding block!\n");

        ret.is_add_rm_cmd = true;
        struct add_rm_t add_rm_cmd;

        add_rm_cmd.action_t = (enum action)ADD;        
        add_rm_cmd.point_t = (enum point)BLOCK;
        add_rm_cmd.block_id = NULL;
        add_rm_cmd.node_id = 0;

        ret.add_rm_cmd = add_rm_cmd;
    }
    else if (my_str_n_compare(buff, "rm block", 8) == true)
    {
        printf("Removing block!\n");

        ret.is_add_rm_cmd = true;
        struct add_rm_t add_rm_cmd;

        add_rm_cmd.action_t = (enum action)REMOVE;        
        add_rm_cmd.point_t = (enum point)BLOCK;
        add_rm_cmd.block_id = NULL;
        add_rm_cmd.node_id = 0;
        
        ret.add_rm_cmd = add_rm_cmd;
    }
    else if (my_str_n_compare(buff, "ls", 2) == true)
    {
        printf("Ls command!\n");

        ret.is_ls_cmd = true;
    }
    else if (my_str_n_compare(buff, "sync", 4) == true)
    {
        printf("Sync command!\n");

        ret.is_sync_cmd = true;
    }
    else
    {
        my_str_write(1, "Command not found\n");
        ret.failure = true;
        return ret;
    }
    
    return ret;
}

int my_prompt_handle(const int fd, struct blockchain_Node **super_node)
{
    char buff[MAX_READ_SIZE];
    for (int i = 0; i < MAX_READ_SIZE; ++i)
    {
        buff[i] = 0;
    }
    const int read_sz = read(fd, &buff, MAX_READ_SIZE);

    if (my_str_nn_compare(buff, "add node", 0, 8) == true)
    {
        //printf("Adding node\n");

        const int node_id = my_str_to_int(buff, 9);
        //printf("%d\n", node_id);

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
    else if (my_str_nn_compare(buff, "add block", 0, 9) == true)
    {
        printf("Adding block\n");
    }
    else if (my_str_nn_compare(buff, "rm node", 0, 7) == true)
    {
        //printf("Removing node\n");

        const int node_id = my_str_to_int(buff, 8);
        //printf("%d\n", node_id);

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
    else if (my_str_nn_compare(buff, "rm block", 0, 8) == true)
    {
        printf("Removing block\n");
    }
    else if (my_str_nn_compare(buff, "sync", 0, 4) == true)
    {
        printf("Syncing!\n");
        // Call sync function
    }
    else if (my_str_nn_compare(buff, "ls", 0, 2) == true)
    {
        //printf("Ls command!\n");
        printNode(*super_node, false);
    }
    else if (my_str_nn_compare(buff, "quit", 0, 4) == true)
    {
        //printf("Quit command!\n");
        return BREAK_READING;
    }
    else
    {
        callErrorSix();
    }

    return CONTINUE_READING;
}

int my_str_to_int(const char *str, const int start_ind)
{
    // Subtracting '\n' (pressing enter creates new line)
    const int str_len = my_str_len(str) - 1;

    if ((str_len - start_ind) == 1 && str[start_ind] == '*')
    {
        return -1;
    }
    else if (str_len < start_ind)
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

void printNode(struct blockchain_Node *node, const bool print_blocks)
{
    struct blockchain_Node *head = node;
    while (head != NULL)
    {
        my_int_write(1, head->nid);
        
        if (print_blocks == true)
        {
            my_str_write(1, ": BLOCKS_WILL_COME_HERE!");
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







struct blockchain_Node* createNode(int nid_numb)
{
    struct blockchain_Node *bc = (struct blockchain_Node *) malloc(sizeof(struct blockchain_Node));
    bc->nid = nid_numb;
    // bc->bid_size =BID_SIZE;
    bc->next = NULL;

    return bc;
    free(bc);
}

void addNode(struct blockchain_Node *node, int nid_numb)
{
    //printf("Hello from addNode!\n");

    struct blockchain_Node* current = node;

    //get last node
    while(current != NULL && current->next != NULL){
        current = current->next;
    }
    //create node with given nid
    struct blockchain_Node* new_Node = createNode(nid_numb);
    if(current==NULL) 
    {
        current = new_Node;
    } 
    else 
    {
        current->next = new_Node;
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

struct blockchain_Node* deleteNode(struct blockchain_Node *node, int nid_numb)
{
    struct blockchain_Node* current = node;
    struct blockchain_Node* newq = NULL;
    while(current) {
        if (nid_numb != current->nid) {
            addNode(newq, current->nid);
        }
    }
    *node=*newq;
    return newq;
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

// struct Storage *createStorage(char *data)
// {
//     struct Storage* ret_storage = (struct Storage *) malloc (sizeof(struct Storage));
//     for (int i = 0; i < READLINE_READ_SIZE; ++i)
//     {
//         ret_storage->buff[i] = data[i];
//     }
//     ret_storage->next = NULL;
//     return ret_storage;
// }

// void addStorage(struct Storage *head, char *data)
// {
//     struct Storage *curr = head;
//     while(curr->next != NULL)
//     {   
//         curr = curr->next;
//     }
//     curr->next = createStorage(data);
// }

// void freeStorage(struct Storage **storage)
// {
//     if (storage != NULL)
//     {
//         while(*storage != NULL)
//         {
//             struct Storage *tmp = *storage;
//             *storage = (*storage)->next;
//             free(tmp);
//         }
//     }
//     free(storage);
// }

// bool isAllZeros(char *buff)
// {
//     for (int i = 0; i < READLINE_READ_SIZE; ++i)
//     {
//         if (buff[i] != 0)
//         {
//             return false;
//         }
//     }
//     return true;
// }



