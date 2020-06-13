#include "../include/error_msgs.h"
#include "../include/helpers.h"

void callErrorOne()
{
    my_str_write(1, "No more resources available on the computer\n");
}

void callErrorTwo()
{
    my_str_write(1, "This node already exists\n");
}

void callErrorThree()
{
    my_str_write(1, "This block already exists\n");
}

void callErrorFour()
{
    my_str_write(1, "Node doesn't exist\n");
}

void callErrorFive()
{
    my_str_write(1, "Block doesn't exist\n");
}

void callErrorSix()
{
    my_str_write(1, "Command not found\n");
}