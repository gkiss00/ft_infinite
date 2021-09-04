#include "./../ft_infinite.h"

// 9 / 3 => 2 ??? 
uint8_t     *division(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size) {
    uint32_t double_size = size * 2;
    uint8_t *a = calloc(double_size, 1);
    uint8_t *b = calloc(double_size, 1);
    uint8_t *tmp = calloc(double_size, 1);
    uint8_t *res = calloc(double_size, 1);
    uint8_t *one = calloc(double_size, 1);

    memcpy(&a[size], nb1, size);
    memcpy(&b[size], nb2, size);
    tmp[double_size - 1] = 1;
    one[double_size - 1] = 1;

    size = double_size;
    
    while(is_inf_or_equal(b, a, size)){
        shift_left(b, size, 1);
        shift_left(tmp, size, 1);
    }

    while(is_sup(tmp, one, size)){
        shift_right(b, size, 1);
        shift_right(tmp, size, 1);
        if(is_sup_or_equal(a, b, size)) {
            uint32_t tmp_sub_size = 0;
            a = substraction(a, b, size, &tmp_sub_size);
            a = add_extra_bytes(a, tmp_sub_size, size);

            uint32_t tmp_add_size = 0;
            res = addition(res, tmp, size, &tmp_add_size);
            res = add_extra_bytes(res, tmp_add_size, size);
        }
    }
    return discard_useless_bytes(res, size, new_size);
}