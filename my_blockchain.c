
#include "my_blockchain.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// struct Storage *createStorage(char *data)
// {
//     struct Storage* ret_storage = (struct Storage *) malloc (sizeof(struct Storage));
//     for (int i = 0; i < READLINE_READ_SIZE; ++i)
//     {
//         ret_storage->buff[i] = data[i];
//     }
//     ret_storage->next = NULL;
//     return ret_storage;
// }

// void addStorage(struct Storage *head, char *data)
// {
//     struct Storage *curr = head;
//     while(curr->next != NULL)
//     {   
//         curr = curr->next;
//     }
//     curr->next = createStorage(data);
// }

// void freeStorage(struct Storage **storage)
// {
//     if (storage != NULL)
//     {
//         while(*storage != NULL)
//         {
//             struct Storage *tmp = *storage;
//             *storage = (*storage)->next;
//             free(tmp);
//         }
//     }
//     free(storage);
// }

// bool isAllZeros(char *buff)
// {
//     for (int i = 0; i < READLINE_READ_SIZE; ++i)
//     {
//         if (buff[i] != 0)
//         {
//             return false;
//         }
//     }
//     return true;
// }
