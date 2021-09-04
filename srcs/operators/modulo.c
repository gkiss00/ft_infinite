#include "./../ft_infinite.h"

// a % b = a - ((a / b) * b)
// examples:
// 3 % 2 == 3 - ((3 / 2) * 2) == 3 - 2 == 1
// 7 % 3 == 7 - ((7 / 3) * 3) == 7 - 6 == 1
// 13 % 7 == 13 - ((13 / 7) * 7) == 13 - 7 == 6
uint8_t     *modulo(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size)
{
    uint32_t tmp_div_size = 0;
    uint8_t *tmp1 = division(nb1, nb2, size, &tmp_div_size);
    tmp1 = add_extra_bytes(tmp1, tmp_div_size, size);

    uint32_t tmp_mlt_size = 0;
    uint8_t *tmp2 = multiplication(tmp1, nb2, size, &tmp_mlt_size);
    tmp2 = add_extra_bytes(tmp2, tmp_mlt_size, size);

    uint32_t tmp_sub_size = 0;
    uint8_t *res = substraction(nb1, tmp2, size, &tmp_sub_size);
    return discard_useless_bytes(res, tmp_sub_size, new_size);
}