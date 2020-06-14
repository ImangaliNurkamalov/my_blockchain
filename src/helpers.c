#include "../include/helpers.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int my_str_len(const char *str)
{
    int count;
    for(count = 0; str[count] != 0; ++count);
    return count;
}

int my_str_write(const int fd, const char *str)
{
    return write(fd, str, my_str_len(str));
}

int my_int_write(const int fd, const int input)
{
    if (input < 0)
    {
        return -1;
    }
    else if (input == 0)
    {
        const int print_digit = 48;
        return write(fd, &print_digit, 1);
    }
    else
    {
        int count_chars_printed = 0;
        int len = 1;
        int temp = input;
        temp /= 10;
        while (temp > 0)
        {
            ++len;
            temp /= 10;
        }

        int print_digit = 48;
        while (len > 0)
        {
            int power_10 = 1;
            for (int j = 1; j < len; ++j)
            {
                power_10 *= 10;
            }

            print_digit = ( input / power_10 ) % 10 + 48;
            count_chars_printed += write(fd, &print_digit, 1);
            --len;
        }
        return count_chars_printed;
    }
}

bool my_str_compare(const char *left, const char *right)
{
    const int left_sz = my_str_len(left);
    const int right_sz = my_str_len(right);

    if (left_sz != right_sz)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < left_sz; ++i)
        {
            if (left[i] != right[i])
            {
                return false;
            }
        }
        return true;
    }
}

bool my_str_nn_compare(const char *left, const char *right, const int start_ind, const int len)
{
    const int left_sz = my_str_len(left);
    const int right_sz = my_str_len(right);

    if (len < 0)
    {
        return false;
    }
    else if (left_sz < start_ind + len)
    {
        return false;
    }
    else if (right_sz < len)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < len; ++i)
        {
            if (left[start_ind + i] != right[i])
            {
                return false;
            }
        }
        return true;
    }
}

char *my_str_copy(const char *str)
{
    const int str_sz = my_str_len(str);
    char *ret_str = (char *) malloc ((str_sz + 1) * sizeof(char));
    for (int i = 0; i < str_sz; ++i)
    {
        ret_str[i] = str[i];
    }
    ret_str[str_sz] = 0;
    return ret_str;
}