#include "block_chain.h"

struct blocks* createBlock(char* data)
{
    struct blocks* bl = (struct blocks *) malloc(sizeof(struct blocks));
    bl->block_data = data;
    bl->next_block = NULL;
    return bl;
}

void addBlock(struct blockchain_Node *node, int nid_numb, char* bid_string)
{
    struct blockchain_Node *current = node;
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
                 struct blocks *current_block = current->bidList->tail;
                 current_block->next_block = new_block;
                 current->bidList->tail = new_block;
                current->bid_array_size++;
            }
        }
        current = current->next;
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