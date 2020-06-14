#include "block_chain.h"
#include "include/helpers.h"

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
    
    // Get last node
    while(current != NULL && current->next != NULL)
    {
        current = current->next;
    }
    
    // Create node with given nid
    struct blockchain_Node* new_Node = createNode(nid_numb);
    current->next = new_Node;
}
struct blockchain_Node *deleteNode(struct blockchain_Node *fisrt_node, int nid_numb)
{
    struct blockchain_Node* head = fisrt_node;
    struct blockchain_Node* current = fisrt_node;
    struct blockchain_Node* previous = current;
    struct blockchain_Node* node_to_delete = NULL;
    struct blocks* tmp_block;
    while(current != NULL)
    {
        if(nid_numb == current->nid)
        {
            node_to_delete = current;            

            if (current == fisrt_node)
            {
                head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            
            break;
        }
        previous = current;
        current = current->next;
    }

    if(node_to_delete != NULL)
    {
        while(node_to_delete->bidList->head != NULL) 
        {
            tmp_block = node_to_delete->bidList->head;
            node_to_delete->bidList->head = node_to_delete->bidList->head->next_block;
            free(tmp_block->block_data);
            free(tmp_block);
        }     
        free(node_to_delete->bidList);
        free(node_to_delete);
    }
    
    return head;
}
void deleteAllNodes(struct blockchain_Node *fisrt_node)
{
    struct blockchain_Node* current = fisrt_node;
    freeBlockChainNode(current);
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
            free(tmp_bid->block_data);
            free(tmp_bid); 
        }
        current = current->next;
        free(tmp->bidList);
        free(tmp);
    }
}

void printNode(struct blockchain_Node *node, const bool print_blocks)
{
    struct blockchain_Node *head = node;
    while (head != NULL)
    {
        my_int_write(1, head->nid);
        
        if (print_blocks == true)
        {
            struct blocks *curr_block = head->bidList->head;
            while(curr_block != NULL)
            {
                if (curr_block == head->bidList->head)
                {
                    my_str_write(1, ": ");
                }

                my_str_write(1, curr_block->block_data);
                
                if (curr_block->next_block != NULL)
                {
                    my_str_write(1, ", ");
                }

                curr_block = curr_block->next_block;
            }
        }

        my_str_write(1, "\n");
        head = head->next;
    }
}

struct blockchain_Node* search_for_a_node(struct blockchain_Node *node, int nid_numb)
{
    struct blockchain_Node* current = node; 
    while(current) 
    {
        if(nid_numb == current->nid) 
        {
            return current;
        }
        current = current->next;
    }
    return current; 
}

int get_blockchain_size(struct blockchain_Node *node)
{
    int count = 0;
    while(node != NULL)
    {
        ++count;
        node = node->next;
    }
    return count;
}