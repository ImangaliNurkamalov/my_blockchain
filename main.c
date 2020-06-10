
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
void deleteNode(struct blockchain_Node *node, int nid_numb);

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

struct blockchain_Node* search_for_a_node(struct blockchain_Node *node, int nid_numb)
{
     struct blockchain_Node* current = node;
     
     while(current)
     {
         if(nid_numb == current->nid) {
             return current;
         }
         current = current->next;
     }
     return current; 
}

void deleteNode(struct blockchain_Node *fisrt_node, int nid_numb)
{
    struct blockchain_Node* current = fisrt_node;
    struct blockchain_Node* previous=current;
    struct blockchain_Node* node_to_delete;

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
            free(node_to_delete);
        }
    }
}

void freeBlockChainNode(struct blockchain_Node *node)
{
    struct blockchain_Node *tmp;
    while(node != NULL)
    {
        tmp = node;
        node = node->next;
        printf("Freeing node with %d\n", tmp->nid);
        free(tmp);
        
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
    deleteNode(first_node, 13);
    
    int i = 0; 
    struct blockchain_Node *current = first_node;
    while(current)
    {
        printf("NODE[%d] : %d\n", i, current->nid);
        i++;
        current = current->next;
    }
    freeBlockChainNode(first_node);
    return 0;
}