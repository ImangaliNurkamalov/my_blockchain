#include "include/my_blockchain.h"

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
    while (i++ < 10)
    {
        const int blockchain_size = get_blockchain_size(*super_node);
        const bool in_sync = is_in_sync(*super_node);
        my_prompt_write(1, in_sync, blockchain_size);
        const int prompt_int = my_prompt_handle(0, super_node);
        if (prompt_int == BREAK_READING)
        {
            // Save and quit
            break;
        }
    }

    freeBlockChainNode(*super_node);
    free(super_node);

    return 0;
}
