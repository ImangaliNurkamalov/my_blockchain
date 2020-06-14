#include "../include/my_read_backup.h"
#include "../include/my_readline.h"
#include "../include/helpers.h"

#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdio.h>

void my_read_backup(struct blockchain_Node **super_node, const char *backup_path)
{
    if (backup_path == NULL)
    {
        my_str_write(1, "No backup blockchain file name specified\n");
        return;
    }
    const int fd = open(backup_path, O_RDONLY);
    if (fd < 0)
    {
        my_str_write(1, "Could not open file name: ");
        my_str_write(1, backup_path);
        my_str_write(1, " for reading backup blockchain!\n");
    }

    bool is_next_node = false;
    bool is_next_block = false;
    int latest_node_id = 0;

    char *str = NULL;
    while ((str = myReadline(fd)) != NULL)
    {
        if (my_str_compare(str, "node") == true)
        {
            is_next_node = true;
            is_next_block = false;
            free(str);
            continue;
        }
        else if (my_str_compare(str, "block") == true)
        {
            is_next_node = false;
            is_next_block = true;
            free(str);
            continue;
        }
        else
        {
            // Do nothing
        }
        if ((is_next_node == true) && (is_next_block == false))
        {
            const int node_id = my_str_to_int_v2(str);
            latest_node_id = node_id;

            if (*super_node == NULL)
            {
                *super_node = createNode(node_id);
            }
            else
            {
                addNode(*super_node, node_id);
            }
        }
        else if ((is_next_node == false) && (is_next_block == true))
        {
            char *bid_copy = my_str_copy(str);
            addBlock(*super_node, latest_node_id, bid_copy);
        }
        else
        {
            // Do nothing
        }
        free(str);
    }
    close(fd);
    freeStorage(big_storage);
}