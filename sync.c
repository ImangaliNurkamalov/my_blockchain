#include "block_chain.h"
#include "include/helpers.h"

void sync_blockchain(struct blockchain_Node *node)
{
    int unique_block_numb;
    struct blockchain_Node *current = node;
    struct blocks *current_head, *block_to_delete;
    char **array_of_blocks = collect_unique_blocks(current, &unique_block_numb);
    while (current != NULL)
    {
        current_head = current->bidList->head;
        if (current_head != NULL)
        {
            while (current_head != NULL)
            {
                block_to_delete = current_head;
                current_head = current_head->next_block;
                free(block_to_delete->block_data);
                free(block_to_delete);
            }
            current->bidList->head = NULL;
            current->bid_array_size = 0;
            for (int i = 0; i < unique_block_numb; i++)
            {
                addBlock(node, current->nid, my_str_copy(array_of_blocks[i]));
            }
        }
        else
        {
            for (int i = 0; i < unique_block_numb; i++)
            {
                addBlock(node, current->nid, my_str_copy(array_of_blocks[i]));
            }
        }
        current = current->next;
    }

    for (int i = 0; i < unique_block_numb; ++i)
    {
        free(array_of_blocks[i]);
    }
    free(array_of_blocks);
}

char **collect_unique_blocks(struct blockchain_Node *node, int *block_numb)
{
    char **blocks = malloc(100 * sizeof(char *));
    int increment = 0;
    struct blockchain_Node *current = node;
    struct blocks *current_head;
    bool unique = true;
    while (current != NULL)
    {
        current_head = current->bidList->head;
        while (current_head != NULL)
        {
            if (increment == 0)
            {
                blocks[increment] = my_str_copy(current_head->block_data);
                increment++;
            }
            else
            {
                unique = true;
                for (int i = 0; i < increment; i++)
                {
                    if (my_str_compare(blocks[i], current_head->block_data) == true)
                    {
                        unique = false;
                    }
                }

                if (unique == true)
                {
                    blocks[increment] = my_str_copy(current_head->block_data);
                    increment++;
                }
            }
            current_head = current_head->next_block;
        }
        current = current->next;
    }
    *block_numb = increment;
    return blocks;
}

bool is_in_sync(struct blockchain_Node *node)
{
    int unique_block_numb = 0;
    struct blockchain_Node *current = node;
    struct blocks *current_head;
    char **array_of_blocks = collect_unique_blocks(current, &unique_block_numb);

    const int size_of_block_chain = get_blockchain_size(current);
    if (size_of_block_chain < 2)
    {
        for (int i = 0; i < unique_block_numb; ++i)
        {
            free(array_of_blocks[i]);
        }
        free(array_of_blocks);
        return false;
    }
    else if (unique_block_numb < 1)
    {
        for (int i = 0; i < unique_block_numb; ++i)
        {
            free(array_of_blocks[i]);
        }
        free(array_of_blocks);
        return false;
    }
    else
    {
        // Do nothing
    }

    for (int i = 0; i < unique_block_numb; ++i)
    {
        current = node;
        bool block_found = false;
        while (current != NULL)
        {
            block_found = false;
            current_head = current->bidList->head;
            while (current_head != NULL)
            {
                if (my_str_compare(array_of_blocks[i], current_head->block_data) == true)
                {
                    block_found = true;
                    break;
                }
                current_head = current_head->next_block;
            }

            if (block_found == false)
            {
                for (int i = 0; i < unique_block_numb; ++i)
                {
                    free(array_of_blocks[i]);
                }
                free(array_of_blocks);
                return false;
            }

            current = current->next;
        }
    }

    for (int i = 0; i < unique_block_numb; ++i)
    {
        free(array_of_blocks[i]);
    }
    free(array_of_blocks);

    return true;
}