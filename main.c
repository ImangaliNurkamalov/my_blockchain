#include "block_chain.h"

int main(int argc, const char* argv[])
{
    // the very first node with nid = 0; its like genesis node.. 
    struct blockchain_Node *first_node=createNode(0);
    addNode(first_node, 1);
    addNode(first_node, 2);
    addNode(first_node, 3);
    addNode(first_node, 4);
    addNode(first_node, 5);
    addNode(first_node, 6);
    addNode(first_node, 7);
    deleteNode(first_node, 2);

    addBlock(first_node,1,"bid1");
    addBlock(first_node,2,"bid2");
    addBlock(first_node,3,"bid3");

    // deleteBlock(first_node, "bid3");

    sync(first_node);

    int i = 0; 
    struct blockchain_Node *current = first_node;
    while(current)
    {
        printf("NODE[%d] -> %d:", i, current->nid);
        i++;
        struct blocks *current_block = current->bidList->head;
        while(current_block != NULL) {
            printf("%s,", current_block->block_data);
            current_block = current_block->next_block;
        }
        printf("\n");
        current = current->next;
    }
    freeBlockChainNode(first_node);
    return 0;
}