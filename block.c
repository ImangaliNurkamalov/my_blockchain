#include "block_chain.h"
#include "include/helpers.h"

struct blocks* createBlock(char* data)
{
    struct blocks* bl = (struct blocks *) malloc(sizeof(struct blocks));
    bl->block_data = data;
    bl->next_block = NULL;
    return bl;
}

int addBlock(struct blockchain_Node *node, int nid_numb, char* bid_string)
{
    struct blockchain_Node *current = node;
    bool found_node = false;
    while(current !=NULL)
    {
         if(nid_numb == current->nid)
         {
             struct blocks *new_block = createBlock(bid_string);
             if(current->bidList->head == NULL) {
                 current->bidList->head = new_block;
                 current->bidList->tail = current->bidList->head; 
                  current->bid_array_size++;
             } else {
                 struct blocks *current_block = current->bidList->head;
                 while (current_block != NULL)
                 {
                     if (my_str_compare(current_block->block_data, bid_string) == true)
                     {
                         free(new_block);
                         return BLOCK_EXISTS;
                     }
                     else if (current_block->next_block == NULL)
                     {
                        break;
                     }
                     else
                     {
                         current_block = current_block->next_block;
                     }
                 }
                 current_block->next_block = new_block;
                 current->bidList->tail = new_block;
                current->bid_array_size++;
            }
            found_node = true;
        }
        current = current->next;
    }
    
    if (found_node == false)
    {
        return NODE_NOT_EXIST;
    }
    else
    {
        return BLOCK_ADDED;
    }
}

void deleteBlock(struct blockchain_Node *node, char* bid_string)
{
     struct blockchain_Node *current = node;
     struct blocks *block_to_delete;
     struct blocks *current_block;
     struct blocks *previous ;
     while(current != NULL)
     {
         int listSize = current->bid_array_size;
         previous = current->bidList->head;
         current_block = current->bidList->head;
         
         while(current_block != NULL)
         {
            block_to_delete = NULL;
            if(strcmp(current_block->block_data, bid_string) == 0)
            {
                if(listSize==1) {
                   current->bidList->head = NULL;
                   current->bid_array_size = 0;
                }
                block_to_delete = current_block;
               
                if (previous == current_block) {
                      current->bidList->head = current_block->next_block;
                      current->bid_array_size--;
                } else
                {
                    previous->next_block = current_block->next_block;
                    current->bid_array_size--;
                }
            }
            previous = current_block;
            current_block = current_block->next_block;
            if(block_to_delete != NULL)
            {
                free(block_to_delete);
            }
        }
        current = current->next;
    }
}