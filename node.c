#include "block_chain.h"

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
    struct blockchain_Node* current = node;
    //get last node
    while(current != NULL && current->next != NULL){
        current = current->next;
    }
    //create node with given nid
    struct blockchain_Node* new_Node = createNode(nid_numb);
    current->next = new_Node;
}
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
