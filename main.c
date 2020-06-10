
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BID_SIZE 10;
struct blockchain_Node {
    int nid;
    // int bid_size;
    // char** bid_array;
    struct blockchain_Node *next;
} blockchain;

struct blockchain_Node* createNode(int nid_numb);
void addNode(struct blockchain_Node *node, int nid);

struct blockchain_Node* search_for_a_node(struct blockchain_Node *node, int nid_numb);
struct blockchain_Node* deleteNode(struct blockchain_Node *node, int nid_numb);

int addBid(struct blockchain_Node *node, int nid_numb, char* bid_string);
int rmBid(struct blockchain_Node *node, char* bid_string);

void freeBlockChainNode(struct blockchain_Node *node);

struct blockchain_Node* createNode(int nid_numb)
{
    struct blockchain_Node *bc = (struct blockchain_Node *) malloc(sizeof(struct blockchain_Node));
    bc->nid = nid_numb;
    // bc->bid_size =BID_SIZE;
    bc->next = NULL;

    return bc;
    free(bc);
}

void addNode(struct blockchain_Node *node, int nid_numb)
{
    printf("Hello from addNode!\n");
    struct blockchain_Node* current = node;
    //get last node
    while(current != NULL && current->next != NULL){
        current = current->next;
    }
    //create node with given nid
    struct blockchain_Node* new_Node = createNode(nid_numb);
    current->next = new_Node;
}

struct blockchain_Node* search_for_a_node(struct blockchain_Node *node, int nid_numb)
{
     struct blockchain_Node* current = node;
     
     while(current) {
         if(nid_numb == current->nid) {
             return current;
         }
         current = current->next;
     }
     return current; 
}

struct blockchain_Node* deleteNode(struct blockchain_Node *node, int nid_numb)
{
    struct blockchain_Node* current = node;
    struct blockchain_Node* new = NULL;
    while(current) {
        if (nid_numb != current->nid) {
            addNode(new, current->nid);
        }
    }
    *node=*new;
    return new;
}

void freeBlockChainNode(struct blockchain_Node *node)
{
     printf("Hello from FREE--FREE!\n");
    struct blockchain_Node *tmp;
    while(node != NULL)
    {
        printf("Hello from FREE!\n");
        tmp = node;
        node = node->next;
        free(tmp);
    }
}


int main(int argc, const char* argv[])
{
   
   // the very first node with nid = 0; its like genesis node.. 
   struct blockchain_Node *first_node=createNode(0);

    addNode(first_node, 12);
    // free(first_node);
    addNode(first_node, 9);
    // free(first_node);
   int i = 0; 
//    struct blockchain_Node *current = new_node2;
//    printf("Current: %p", current);
    struct blockchain_Node *current = first_node;
     while(current) {
         printf("NODE[%d] : %d\n", i, current->nid);
         i++;
         current = current->next;
     }
    freeBlockChainNode(first_node);
    // free(first_node);
    return 0;
}