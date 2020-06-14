#include "include/my_blockchain.h"
#include "include/my_save.h"
#include "include/my_read_backup.h"

#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdio.h>

int main(int argc, const char *argv[])
{
    struct blockchain_Node **super_node = (struct blockchain_Node **)malloc(sizeof(struct blockchain_Node *));
    *super_node = NULL;

    // Read backup blockchain (By default first argument will be backup file name, if not specified no backup will be read)
    const char *backup_path = (argc > 1) ? argv[1] : NULL;
    my_read_backup(super_node, backup_path);

    // Run main blockchian process
    my_blockchain(super_node);  

    // Save blockchain (By default second argument will be save blockchain file name, if not specified no blockchain will be saved)
    const char *save_path = (argc > 2) ? argv[2] : NULL;
    my_save(*super_node, save_path);

    // Clean up blockchain memory
    freeBlockChainNode(*super_node);
    free(super_node);

    return 0;
}
