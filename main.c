#include <stdio.h>

struct blockchain_Node {
    int nid;
    char** bid;
    struct blockchain_Node *next;
};


int addNode(struct blockchain_Node *node, int nid);
int rmNode(struct blockchain_Node *node, int nid);
int addBid(struct blockchain_Node *node, int nid, char* bid_string);
int rmBid(struct blockchain_Node *node,char* bid_string);

int main(int argc, const char* argv[])
{
 

    return 0;
}