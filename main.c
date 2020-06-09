
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BID_SIZE 10;
struct blockchain_Node {
    int nid;
    int bid_size;
    char** bid_array;
    struct blockchain_Node *next;
} blockchain;

struct blockchain_Node* createNode(int nid_numb);
void addNode(struct blockchain_Node *node, int nid);

struct blockchain_Node* search_for_a_node(struct blockchain_Node *node, int nid_numb);
void deleteNode(struct blockchain_Node *node, int nid_numb);

int addBid(struct blockchain_Node *node, int nid_numb, char* bid_string);
int rmBid(struct blockchain_Node *node, char* bid_string);

struct blockchain_Node* createNode(int nid_numb)
{
    struct blockchain_Node *bc = (struct blockchain_Node *) malloc(sizeof(struct blockchain_Node));
    bc->nid = nid_numb;
    bc->bid_size =BID_SIZE;
    bc->next = NULL;

    return bc;
}

void addNode(struct blockchain_Node *node, int nid_numb)
{
    struct blockchain_Node* current = node;

    //get last node
    while(current != NULL && current->next != NULL){
        current = current->next;
    }
    //create node with given nid
    struct blockchain_Node* new_Node = createNode(nid_numb);
    // add new node to the list
    if(current==NULL) {
        current = new_Node;
    } else {
        current->next = new_Node;
    }
    
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

void deleteNode(struct blockchain_Node *node, int nid_numb)
{
    struct blockchain_Node* current = node;
    struct blockchain_Node* new = NULL;
    while(current) {
        if (nid_numb != current->nid) {
            addNode(new, current->nid);
        }
    }
    *node=*new;
}

int main(int argc, const char* argv[])
{
  
   struct blockchain_Node *first_node = NULL;
   addNode(first_node, 12);
   addNode(first_node, 13);
   int i = 0; 
   struct blockchain_Node *current = first_node;
  while(current) {
      printf("NODE[%d] : %d", i, first_node->nid);
      i++;
      current = current->next;
      free(current);
  }
//   free(first_node);
    return 0;
}