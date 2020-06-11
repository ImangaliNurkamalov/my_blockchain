#include "my_blockchain.h"

#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdio.h>

int main(int argc, const char* argv[])
{

    struct blockchain_Node **super_node = (struct blockchain_Node **) malloc (sizeof(struct blockchain_Node *));
    *super_node = NULL;

    // READING BACKUP BLOCKCHAIN

    int i = 0;
    while (i++ < 5)
    {
        const int blockchain_size = get_blockchain_size(*super_node);
        my_prompt_write(1, true, blockchain_size);
        const int prompt_int = my_prompt_handle(0, super_node);
        if (prompt_int == BREAK_READING)
        {
            // Save and quit
            break;
        }
    }












    // printf("Hello from main!\n");
    // struct blockchain_Node *first_node=createNode(0);

    // addNode(first_node, 12);
    // addNode(first_node, 9);
    // int i = 0; 
    // struct blockchain_Node *tmp_head = first_node;
    // while(tmp_head) 
    // {
    //     printf("NODE[%d] : %d\n", i, tmp_head->nid);
    //     i++;
    //     tmp_head = tmp_head->next;
    // }

    // struct blockchain_Node *tmp;
    // while(first_node != NULL)
    // {
    //     tmp = first_node;
    //     first_node = first_node->next;
    //     free(tmp);
    // }
    // free(first_node);

    return 0;
}
