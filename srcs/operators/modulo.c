#include "./../ft_infinite.h"

uint8_t     *modulo(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size)
{
    uint8_t *tmp1 = division(nb1, nb2, size, new_size);
    tmp1 = add_extra_bytes(tmp1, *new_size, size);
    uint8_t *tmp2 = multiplication(tmp1, nb2, size, new_size);
    tmp2 = add_extra_bytes(tmp2, *new_size, size);
    uint8_t *res = substraction(nb1, tmp2, size, new_size);
    return discard_useless_bytes(res, *new_size, new_size);
}