#include "./../ft_infinite.h"

uint8_t     *exponent(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size) {
    // make a copy of nb1 and nb2
    uint8_t *a = calloc(size, 1);
    uint8_t *b = calloc(size, 1);
    uint8_t *one = calloc(size, 1);
    uint8_t *res = calloc(size, 1);
    memcpy(a, nb1, size);
    memcpy(b, nb2, size);
    one[size - 1] = 1;
    memcpy(res, a, size);

    uint32_t current_size = size;
    // while b > 1
    while(is_sup(b, one, size) == true) {
        // multiply res by a
        // then apply new size to a
        uint32_t tmp_res_size = 0;
        res = multiplication(res, a, current_size, &tmp_res_size);
        a = add_extra_bytes(a, current_size, tmp_res_size);

        // subtract 1 to b
        // then restore size of b;
        uint32_t tmp_b_size = 0;
        b = substraction(b, one, size, &tmp_b_size);
        b = add_extra_bytes(b, tmp_b_size, size);

        // actualize the current size
        current_size = tmp_res_size;
    }
    return discard_useless_bytes(res, current_size, new_size);
}