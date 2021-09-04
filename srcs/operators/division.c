#include "./../ft_infinite.h"

// 9 / 3 => 2 ??? 
uint8_t     *division(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size) {
    uint8_t *a = calloc(size, 1);
    uint8_t *b = calloc(size, 1);
    memcpy(a, nb1, size);
    memcpy(b, nb2, size);

    a = add_extra_bytes(a, size, size + 1);
    b = add_extra_bytes(b, size, size + 1);
    size += 1;
    uint8_t *tmp = calloc(size, 1);
    uint8_t *res = calloc(size, 1);
    uint8_t *one = calloc(size, 1);
    tmp[size - 1] = 1;
    one[size - 1] = 1;

    while(is_inf_or_equal(b, a, size)){
        shift_left(b, size, 1);
        shift_left(tmp, size, 1);
    }
    while(is_sup(tmp, one, size)){
        shift_right(b, size, 1);
        shift_right(tmp, size, 1);
        if(is_sup(a, b, size)) {
            uint32_t tmp_size = 0;
            a = substraction(a, b, size, &tmp_size);
            a = add_extra_bytes(a, tmp_size, size);
            res = addition(res, tmp, size, &tmp_size);
            res = add_extra_bytes(res, tmp_size, size);
        }
    }
    return discard_useless_bytes(res, size, new_size);
}