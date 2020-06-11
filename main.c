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

void addBid(struct blockchain_Node *node, int nid_numb, char* bid_string);
void rmBid(struct blockchain_Node *node, char* bid_string);

void freeBlockChainNode(struct blockchain_Node *node);
void freeBlocks(struct blockchain_Node *node);

struct blockchain_Node* createNode(int nid_numb)
{
    struct blockchain_Node *bc = (struct blockchain_Node *) malloc(sizeof(struct blockchain_Node));
    bc->nid = nid_numb;
    bc->bid_array_size = 0;
    bc->bidList = NULL;
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

// void addBid(struct blockchain_Node *node, int nid_numb, char* bid_string)
// {

//     struct blockchain_Node *current = node;
       
//      while(current !=NULL)
//      {
//          if(nid_numb == current->nid)
//          {
//              struct blocks* new_block = createBlock(bid_string);  
//              if(current->bidList == NULL) {
//                 current->bidList = new_block;
//              }
//             //  while(current->bid != NULL)
//             //  {
//             //      current->bid = current->bid->next_block;
//             //     }
//             //  current->bid->block_data = bid_string;
//             //  current->bid->next_block = NULL;
//              current->bid_array_size++;
//          }
//          current = current->next;
//      }
// }
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

// void deleteNode(struct blockchain_Node *fisrt_node, int nid_numb)
// {
//     struct blockchain_Node* current = fisrt_node;
//     struct blockchain_Node* previous=current;
//     struct blockchain_Node* node_to_delete;
//     while(current != NULL)
//     {
//         node_to_delete = NULL;
//         if(nid_numb == current->nid) {
//             node_to_delete = current;
//             previous->next=current->next;
//         }
//         previous = current;
//         current = current->next;
//         if(node_to_delete != NULL)
//         {
//             free(node_to_delete->bid);
//             free(node_to_delete);
//         }
//     }
// }
// void deleteAllNodes(struct blockchain_Node *fisrt_node)
// {
//     struct blockchain_Node* current = fisrt_node;
//     struct blockchain_Node* need_to_free = fisrt_node->next;
//     current->next=NULL;
//     freeBlockChainNode(need_to_free);

// }

// void freeBlocks(struct blockchain_Node *node)
// {
//     struct blockchain_Node *current = node;
//     struct blocks *tmp_bid;
//     printf("Hello from FreeBlocks!");

//           while(current) {
//             printf("Hello from tmp->bid");
//             if(current->bid != NULL) {
//                 tmp_bid = current->bid;
//                 current->bid = current->bid->next_block; 
//                 free(tmp_bid);
//             }
//             current = current->next;
//         }
// }
  
void freeBlockChainNode(struct blockchain_Node *node)
{
      printf("Hello from freeBlockChainNode!\n");
    // struct blocks *tmp_bid;
    struct blockchain_Node *tmp;
    struct blockchain_Node *current = node;
    while(current != NULL)
    {
         printf("Free: %d\n", current->nid);
        tmp = current;
        //     for (int index=0; index<tmp->bid_array_size; index++) {
                    
        //         if(tmp->bid->block_data != NULL) {
                    
        //             tmp_bid = tmp->bid;
        //             tmp->bid = tmp->bid->next_block;
        //              printf("Free: %s\n", tmp_bid->block_data);
        //             free(tmp_bid); 
        //         }     

        // }
        current = current->next;
        
        free(tmp);
    }
}

// void rmBid(struct blockchain_Node *node, char* bid_string)
// {
//      struct blockchain_Node *current = node;
//      struct blocks *previous_block = current->bid;
//      struct blocks *block_to_delete;  
//      while(current !=NULL)
//      {
//          block_to_delete = NULL;
//          while (current->bid) {
//              if (strcmp(bid_string,current->bid->block_data)==0)
//              {
//                  block_to_delete = current->bid;
//                  previous_block->next_block = current->bid->next_block;
//              }
//              previous_block = current->bid;
//              current->bid = current->bid->next_block;
//              if(block_to_delete != NULL)
//              {
//                  free(block_to_delete);
//              }
//          }
//          current = current->next;
//      }

// }

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

    // addBid(first_node,13,"bid1");
    // addBid(first_node,2,"bid2");
    // addBid(first_node,2,"morebidAt2");
    // rmBid(first_node, "bid1");

    // deleteNode(first_node,1);
    // deleteAllNodes(first_node);
    
    int i = 0; 
    struct blockchain_Node *current = first_node;
    while(current)
    {
        printf("NODE[%d] -> %d: and bid: %p ", i, current->nid, current->bidList);
        i++;
        while(current->bidList->head != NULL) {
            printf("%p, ", current->bidList->head);
            current->bidList->head = current->bidList->head->next_block;
        }
        printf("\n");
        current = current->next;
    }
    // freeBlocks(first_node);
    freeBlockChainNode(first_node);
    return 0;
}