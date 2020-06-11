#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BID_SIZE 10;

struct blockList {
    struct blocks *head;
    struct blocks *tail;
};

struct blocks {
    char* block_data;
    struct blocks *next_block;
};


struct blockchain_Node {
    int nid;
    int bid_array_size;
    struct blockList *bidList;
    bool sync;
    struct blockchain_Node *next;
} blockchain;

struct blockchain_Node* createNode(int nid_numb);
void addNode(struct blockchain_Node *node, int nid);

struct blockchain_Node* search_for_a_node(struct blockchain_Node *node, int nid_numb);
void deleteNode(struct blockchain_Node *node, int nid_numb);
void deleteAllNodes(struct blockchain_Node *fisrt_node);

void addBlock(struct blockchain_Node *node, int nid_numb, char* bid_string);
void deleteBlock(struct blockchain_Node *node, char* bid_string);

void freeBlockChainNode(struct blockchain_Node *node);
void freeBlocks(struct blockchain_Node *node);

struct blockchain_Node* createNode(int nid_numb)
{
    struct blockchain_Node *bc = (struct blockchain_Node *) malloc(sizeof(struct blockchain_Node));
    bc->nid = nid_numb;
    bc->bid_array_size = 0;
    bc->bidList = (struct blockList *) malloc(sizeof(struct blockList));
    bc->bidList->head = NULL;
    bc->bidList->tail = NULL;
    bc->next = NULL;

    return bc;
}


void addNode(struct blockchain_Node *node, int nid_numb)
{
    // printf("Hello from addNode!\n");
    struct blockchain_Node* current = node;
    //get last node
    while(current != NULL && current->next != NULL){
        current = current->next;
    }
    //create node with given nid
    struct blockchain_Node* new_Node = createNode(nid_numb);
    current->next = new_Node;
}

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
// struct blockchain_Node* search_for_a_node(struct blockchain_Node *node, int nid_numb)
// {
//      struct blockchain_Node* current = node;
//      while(current)
//      {
//          if(nid_numb == current->nid) {
//              return current;
//          }
//          current = current->next;
//      }
//      return current; 
// }

void deleteNode(struct blockchain_Node *fisrt_node, int nid_numb)
{
    struct blockchain_Node* current = fisrt_node;
    struct blockchain_Node* previous=current;
    struct blockchain_Node* node_to_delete;
    struct blocks* tmp_block;
    while(current != NULL)
    {
        node_to_delete = NULL;
        if(nid_numb == current->nid) {
            node_to_delete = current;
            previous->next=current->next;
        }
        previous = current;
        current = current->next;
        if(node_to_delete != NULL)
        {
            while(node_to_delete->bidList->head != NULL) {
                tmp_block = node_to_delete->bidList->head;
                node_to_delete->bidList->head = node_to_delete->bidList->head->next_block;
                // printf("Free tmp_bid->block_data: %p\n", tmp_block);
                free(tmp_block);
                }     
            free(node_to_delete->bidList);
            free(node_to_delete);
        }
    }
}
void deleteAllNodes(struct blockchain_Node *fisrt_node)
{
    struct blockchain_Node* current = fisrt_node;
    struct blockchain_Node* need_to_free = fisrt_node->next;
    current->next=NULL;
    freeBlockChainNode(need_to_free);

}

void freeBlockChainNode(struct blockchain_Node *node)
{
    struct blocks *tmp_bid;
    struct blockchain_Node *tmp;
    struct blockchain_Node *current = node;
    while(current != NULL)
    {
        tmp = current;
        while(tmp->bidList->head != NULL)
        {
            tmp_bid = tmp->bidList->head;
            tmp->bidList->head = tmp->bidList->head->next_block;
            free(tmp_bid); 
        }
        current = current->next;
        free(tmp->bidList);
        free(tmp);
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
                }
                block_to_delete = current_block;
               
                if (previous == current_block) {
                      current->bidList->head = current_block->next_block;
                } else
                {
                    previous->next_block = current_block->next_block;
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

int main(int argc, const char* argv[])
{
    // the very first node with nid = 0; its like genesis node.. 
    struct blockchain_Node *first_node=createNode(0);
    addNode(first_node, 13);
    addNode(first_node, 0);
    addNode(first_node, 13);
    addNode(first_node, 1);
    addNode(first_node, 13);
    addNode(first_node, 2);
    addNode(first_node, 13);

    addBlock(first_node,13,"bid1");
    addBlock(first_node,13,"33333");
    // addBid(first_node,2,"bid2");
    addBlock(first_node,2,"33333");
    // addBid(first_node,2,"33333");
    deleteBlock(first_node, "33333");
     deleteBlock(first_node, "bid2");

    deleteNode(first_node,13);
    // deleteAllNodes(first_node);
    
    int i = 0; 
    struct blockchain_Node *current = first_node;
    while(current)
    {
        printf("NODE[%d] -> %d:", i, current->nid);
        i++;
        struct blocks *current_block = current->bidList->head;
        while(current_block != NULL) {
            printf("%s, ", current_block->block_data);
            current_block = current_block->next_block;
        }
        printf("\n");
        current = current->next;
    }
    freeBlockChainNode(first_node);
    return 0;
}