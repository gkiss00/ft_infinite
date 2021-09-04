#include "./../ft_infinite.h"


// something is wrong
uint8_t *multiplication(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size)
{
    // make a copy of nb1 and nb2 with bigger buff
    uint32_t double_size = size * 2;
    uint8_t *a = calloc(double_size, 1);
    uint8_t *b = calloc(double_size, 1);
    uint8_t *res = calloc(double_size, 1);
    memcpy(&a[size], nb1, size);
    memcpy(&b[size], nb2, size);

    uint32_t current_size = double_size;
    // While second number doesn't become 1
    while (is_zero(b, current_size) == false)
    {
        if(b[current_size -1] & 1){
            uint32_t tmp_size = 0;
            res = addition(res, a, current_size, &tmp_size);
            res = add_extra_bytes(res, tmp_size, current_size);
        }
        // Double the first number and halve the second number
        shift_left(a, current_size, 1);
        shift_right(b, current_size, 1);
    }
    res = discard_useless_bytes(res, current_size, new_size);
    return res;
}