#ifndef FT_INFINITE_H
#define FT_INFINITE_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <limits.h>

#define MALLOC_ERROR "Malloc error, exit"
#define CMD_ERROR "Command not found, exit"
#define ODD_ERROR "Number is odd, exit"
#define ARG_ERROR "Number arg is wrong, exit"
#define INPUT_ERROR "bad input, exit"

#define PRINT_UINT64(n) print_uint8(&((uint8_t *)n)[0]), printf(" "), print_uint8(&((uint8_t *)n)[1]), printf(" "), print_uint8(&((uint8_t *)n)[2]), printf(" "), print_uint8(&((uint8_t *)n)[3]), printf(" "), print_uint8(&((uint8_t *)n)[4]), printf(" "), print_uint8(&((uint8_t *)n)[5]), printf(" "), print_uint8(&((uint8_t *)n)[6]), printf(" "), print_uint8(&((uint8_t *)n)[7])
#define PRINT_UINT56(n) print_uint8(&((uint8_t *)n)[0]), printf(" "), print_uint8(&((uint8_t *)n)[1]), printf(" "), print_uint8(&((uint8_t *)n)[2]), printf(" "), print_uint8(&((uint8_t *)n)[3]), printf(" "), print_uint8(&((uint8_t *)n)[4]), printf(" "), print_uint8(&((uint8_t *)n)[5]), printf(" "), print_uint8(&((uint8_t *)n)[6])
#define PRINT_UINT48(n) print_uint8(&((uint8_t *)n)[0]), printf(" "), print_uint8(&((uint8_t *)n)[1]), printf(" "), print_uint8(&((uint8_t *)n)[2]), printf(" "), print_uint8(&((uint8_t *)n)[3]), printf(" "), print_uint8(&((uint8_t *)n)[4]), printf(" "), print_uint8(&((uint8_t *)n)[5]), printf(" ")
#define PRINT_UINT40(n) print_uint8(&((uint8_t *)n)[0]), printf(" "), print_uint8(&((uint8_t *)n)[1]), printf(" "), print_uint8(&((uint8_t *)n)[2]), printf(" "), print_uint8(&((uint8_t *)n)[3]), printf(" "), print_uint8(&((uint8_t *)n)[4])
#define PRINT_UINT32(n) print_uint8(&((uint8_t *)n)[0]), printf(" "), print_uint8(&((uint8_t *)n)[1]), printf(" "), print_uint8(&((uint8_t *)n)[2]), printf(" "), print_uint8(&((uint8_t *)n)[3])
#define PRINT_UINT24(n) print_uint8(&((uint8_t *)n)[0]), printf(" "), print_uint8(&((uint8_t *)n)[1]), printf(" "), print_uint8(&((uint8_t *)n)[2])
#define PRINT_UINT16(n) print_uint8(&((uint8_t *)n)[0]), printf(" "), print_uint8(&((uint8_t *)n)[1])
#define PRINT_UINT8(n) print_uint8(&((uint8_t *)n)[0])

typedef struct              s_command
{
    uint8_t                 *name;
    uint8_t                 *(*operator)(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size);
    uint32_t                nb_bytes;
    struct s_command        *next;
}                           t_command;

// CONVERTERS
uint8_t     *str_to_hex(uint8_t *str, uint32_t size);
uint8_t     *str_to_bin(uint8_t *str, uint32_t size);

// OPERATORS
uint8_t     *addition(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size);
uint8_t     *substraction(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size);
uint8_t     *multiplication(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size);
uint8_t     *division(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size);
uint8_t     *modulo(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size);
uint8_t     *exponent(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size);

uint8_t     *superior(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size);
uint8_t     *inferior(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size);
uint8_t     *equal(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size);
uint8_t     *not_equal(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size);
uint8_t     *superior_or_equal(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size);
uint8_t     *inferior_or_equal(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size);

uint8_t     *not(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size);
uint8_t     *and(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size);
uint8_t     *or(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size);
uint8_t     *xor(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size);
uint8_t     *right_shift(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size);
uint8_t     *left_shift(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size);
uint8_t     *right_rotate(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size);
uint8_t     *left_rotate(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size);

// OPERATORS-UTILS
bool        is_zero(uint8_t *nb1, uint32_t size);
bool        is_sup(uint8_t *nb1, uint8_t *nb2, uint32_t size);
bool        is_inf(uint8_t *nb1, uint8_t *nb2, uint32_t size);
bool        is_sup_or_equal(uint8_t *nb1, uint8_t *nb2, uint32_t size);
bool        is_inf_or_equal(uint8_t *nb1, uint8_t *nb2, uint32_t size);
uint8_t     *add_extra_bytes(uint8_t *nb, uint32_t size, uint32_t new_size);
uint8_t     *discard_useless_bytes(uint8_t *nb, uint32_t size, uint32_t *new_size);
void        shift_left(uint8_t *number, uint32_t size, uint32_t bit);
void        shift_right(uint8_t *number, uint32_t size, uint32_t bit);

// UTILS
void        exit_error(char *error);
void        print_uint8(uint8_t *n);
void        print_number_hexa(uint8_t *n, uint32_t size);

// NODE
t_command   *new_command(uint8_t *name, uint8_t *(*operator)(uint8_t*, uint8_t*, uint32_t, uint32_t*));
t_command   *command_last(t_command *command);
void        command_add_back(t_command **head, t_command *new);
#endif