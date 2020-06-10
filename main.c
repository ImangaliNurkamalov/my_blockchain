#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BID_SIZE 10;

struct blockchain_Node {
    int nid;
    int bid_array_size;
    char** bid_array;
    bool sync;
    struct blockchain_Node *next;
} blockchain;

struct blockchain_Node* createNode(int nid_numb);
void addNode(struct blockchain_Node *node, int nid);

struct blockchain_Node* search_for_a_node(struct blockchain_Node *node, int nid_numb);
void deleteNode(struct blockchain_Node *node, int nid_numb);
void deleteAllNodes(struct blockchain_Node *fisrt_node);

void addBid(struct blockchain_Node *node, int nid_numb, char* bid_string);
int rmBid(struct blockchain_Node *node, char* bid_string);

void freeBlockChainNode(struct blockchain_Node *node);

struct blockchain_Node* createNode(int nid_numb)
{
    struct blockchain_Node *bc = (struct blockchain_Node *) malloc(sizeof(struct blockchain_Node));
    bc->nid = nid_numb;
    bc->bid_array_size = 0;
    bc->bid_array = malloc(10*sizeof(char*));
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
            free(node_to_delete->bid_array);
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
    struct blockchain_Node *tmp;
    while(node != NULL)
    {
        tmp = node;
        node = node->next;
        free(tmp->bid_array);
        free(tmp);
    }
}

void addBid(struct blockchain_Node *node, int nid_numb, char* bid_string)
{
    struct blockchain_Node *current = node;
       
     while(current !=NULL)
     {
         if(nid_numb == current->nid)
         {
             current->bid_array[current->bid_array_size] = bid_string;
             current->bid_array_size++;
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
    addBid(first_node,13,"bid1");
    addBid(first_node,2,"bid2");
    deleteNode(first_node,1);
    // deleteAllNodes(first_node);
    
    int i = 0; 
    struct blockchain_Node *current = first_node;
    while(current)
    {
        printf("NODE[%d] -> %d: ", i, current->nid);
        i++;
        for(int i = 0; i < current->bid_array_size; i++) {
            printf("%s, ", current->bid_array[i]);
        }
        printf("\n");
        current = current->next;
    }
    freeBlockChainNode(first_node);
    return 0;
}