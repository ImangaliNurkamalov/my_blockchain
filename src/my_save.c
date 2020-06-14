#include "../include/my_save.h"
#include "../include/helpers.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void my_save(struct blockchain_Node *super_node, const char *save_path)
{
    if (save_path == NULL)
    {
        my_str_write(1, "No save blockchain file name specified\n");
        return;
    }
   
    const int fd = open(save_path, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
    
    struct blockchain_Node *current = super_node;
    struct blocks *current_block;
    while (current != NULL)
    {
        my_str_write(fd, "node\n");
        my_int_write(fd, current->nid);
        my_str_write(fd, "\n");

        current_block = current->bidList->head;
        while (current_block != NULL)
        {
            if (current_block == current->bidList->head)
            {
                my_str_write(fd, "block\n");
            }
            my_str_write(fd, current_block->block_data);
            my_str_write(fd, "\n");

            current_block = current_block->next_block;
        }

        current = current->next;
    }

    close(fd);
}