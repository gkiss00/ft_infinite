#include "./../ft_infinite.h"

void exit_error(char *error)
{
    fprintf(stderr, "%s\n", error);
    exit(EXIT_FAILURE);
}

void print_uint8(uint8_t *n)
{
    int t = *n;
    for (int i = 0; i < 8; ++i)
    {
        if (t / pow(2, 7 - i) >= 1)
        {
            putchar('1');
            t -= pow(2, 7 - i);
        }
        else
        {
            putchar('0');
        }
    }
}

void print_number_hexa(uint8_t *n, uint32_t size)
{
    for(uint32_t i = 0; i < size; ++i) {
        printf("%02x", n[i]);
    }
}