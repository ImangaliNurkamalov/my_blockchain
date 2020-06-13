#include "block_chain.h"

void sync_blockchain(struct blockchain_Node *node)
{
    int unique_block_numb;
    struct blockchain_Node *current = node;
    struct blocks *current_head, *block_to_delete;
    char ** array_of_blocks = collect_uniue_blocks(current, &unique_block_numb);
   
    while(current)
    {
        current_head = current->bidList->head;
        if(current_head != NULL)
        {
            while(current_head){
                block_to_delete = current_head;
                current_head= current_head->next_block;
                free(block_to_delete);
            }     
            current->bidList->head = NULL;
            current->bid_array_size = 0;
                
            for(int i=0; i<unique_block_numb; i++)
            {
            addBlock(current,current->nid,array_of_blocks[i]);
            }
        } else {
            for(int i=0; i<unique_block_numb; i++)
            {
            addBlock(current,current->nid,array_of_blocks[i]);
            }
        }
        current = current->next;
    }
 free(array_of_blocks);
}

char** collect_uniue_blocks(struct blockchain_Node *node, int *block_numb)
{
    char ** blocks = malloc(100 * sizeof(char *));
    int increment = 0;
    struct blockchain_Node *current = node;
    struct blocks *current_head;  
    bool unique = true;
    while(current != NULL)
    {
        current_head = current->bidList->head;
        while(current_head != NULL)
        {
            if(increment == 0)
            {
                blocks[increment] = current_head->block_data;
                
            } else {
                for(int i=0; i<increment; i++)
                {
                    if(strcmp(blocks[i], current_head->block_data)==0)
                    {
                        unique=false;
                    }
                }
                if(unique)
                {
                    blocks[increment] =  current_head->block_data;
                }
            }
            increment++;
            current_head = current_head->next_block;
        }
        current_head = NULL;
       current = current->next;
    }
    *block_numb = increment;
    return blocks;
}