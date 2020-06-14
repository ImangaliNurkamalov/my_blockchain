#include "../include/my_readline.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *myReadline(int fd)
{
    // Do not continue for not successful file description
    if (fd < 0)
    {
        return NULL;
    }

    // Initialize storage memory
    if (big_storage == NULL)
    {
        big_storage = (struct Storage **)malloc(sizeof(struct Storage *));
        *big_storage = NULL;

        // Read all contents of the file and store
        while (true)
        {
            char buff[READLINE_READ_SIZE];
            int read_sz = read(fd, buff, READLINE_READ_SIZE);
            if (read_sz < 1)
            {
                break;
            }

            if (read_sz != READLINE_READ_SIZE)
            {
                for (int i = read_sz; i < READLINE_READ_SIZE; ++i)
                {
                    buff[i] = 0;
                }
            }

            if (*big_storage == NULL)
            {
                *big_storage = createStorage(buff);
            }
            else
            {
                addStorage(*big_storage, buff);
            }
        }
    }

    // Find out how much memory is needed
    bool is_non_zero = false;
    bool is_terminated = false;
    bool is_new_line = false;
    int capacity = 0;
    struct Storage *tmp_head = *big_storage;
    while (tmp_head != NULL)
    {
        if (isAllZeros(tmp_head->buff) == true)
        {
            tmp_head = tmp_head->next;
        }
        else
        {
            for (int i = 0; i < READLINE_READ_SIZE; ++i)
            {
                if (tmp_head->buff[i] == 0)
                {
                    if (is_non_zero == false)
                    {
                        continue;
                    }
                    else
                    {
                        is_terminated = true;
                        break;
                    }
                }
                else if (tmp_head->buff[i] == '\n')
                {
                    is_new_line = true;
                    break;
                }
                else
                {
                    is_non_zero = true;
                    ++capacity;
                }
            }

            if (is_terminated == true || is_new_line == true)
            {
                break;
            }
            else
            {
                tmp_head = tmp_head->next;
            }
        }
    }

    // If nothing is needed then break
    if (capacity < 1)
    {
        return NULL;
    }

    // Populate return string based on capacity defined and set old elements to zeros
    char *ret_str = (char *)malloc((capacity + 1) * sizeof(char));
    is_non_zero = false;
    is_terminated = false;
    is_new_line = false;
    capacity = 0;
    tmp_head = *big_storage;
    while (tmp_head != NULL)
    {
        if (isAllZeros(tmp_head->buff) == true)
        {
            tmp_head = tmp_head->next;
        }
        else
        {
            for (int i = 0; i < READLINE_READ_SIZE; ++i)
            {
                if (tmp_head->buff[i] == 0)
                {
                    if (is_non_zero == false)
                    {
                        continue;
                    }
                    else
                    {
                        is_terminated = true;
                        break;
                    }
                }
                else if (tmp_head->buff[i] == '\n')
                {
                    is_new_line = true;
                    tmp_head->buff[i] = 0;
                    break;
                }
                else
                {
                    is_non_zero = true;
                    ret_str[capacity++] = tmp_head->buff[i];
                    tmp_head->buff[i] = 0;
                }
            }

            if (is_terminated == true || is_new_line == true)
            {
                break;
            }
            else if (isAllZeros((*big_storage)->buff) == true)
            {
                // Do nothing
            }
            else
            {
                // Something went wrong! STOP!
                break;
            }
        }
    }
    ret_str[capacity] = 0;
    return ret_str;
}

struct Storage *createStorage(char *data)
{
    struct Storage *ret_storage = (struct Storage *)malloc(sizeof(struct Storage));
    for (int i = 0; i < READLINE_READ_SIZE; ++i)
    {
        ret_storage->buff[i] = data[i];
    }
    ret_storage->next = NULL;
    return ret_storage;
}

void addStorage(struct Storage *head, char *data)
{
    struct Storage *curr = head;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = createStorage(data);
}

void freeStorage(struct Storage **storage)
{
    if (storage != NULL)
    {
        while (*storage != NULL)
        {
            struct Storage *tmp = *storage;
            *storage = (*storage)->next;
            free(tmp);
        }
    }
    free(storage);
}

bool isAllZeros(char *buff)
{
    for (int i = 0; i < READLINE_READ_SIZE; ++i)
    {
        if (buff[i] != 0)
        {
            return false;
        }
    }
    return true;
}