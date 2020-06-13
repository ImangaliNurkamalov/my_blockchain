#include <stdbool.h>

int my_str_len(const char *str);
int my_str_write(const int fd, const char *str);
int my_int_write(const int fd, const int input);
bool my_str_compare(const char *left, const char *right);
bool my_str_nn_compare(const char *left, const char *right, const int start_ind, const int len);