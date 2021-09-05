#include "./../ft_infinite.h"

uint8_t *get_nb_turn(uint8_t *nb1, uint32_t size, uint32_t *new_size);

uint8_t *not(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size) {
    uint8_t *res = calloc(size, 1);

    (void)nb2;
    for (uint32_t i = 0; i < size; ++i){
        res[i] = ~nb1[i];
    }
    *new_size = size;
    return res;
}

uint8_t *and(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size) {
    uint8_t *res = calloc(size, 1);

    for (uint32_t i = 0; i < size; ++i){
        res[i] = nb1[i] & nb2[i];
    }
    *new_size = size;
    return res;
}

uint8_t *or(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size) {
    uint8_t *res = calloc(size, 1);

    for (uint32_t i = 0; i < size; ++i){
        res[i] = nb1[i] | nb2[i];
    }
    *new_size = size;
    return res;
}

uint8_t *xor(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size) {
    uint8_t *res = calloc(size, 1);

    for (uint32_t i = 0; i < size; ++i){
        res[i] = nb1[i] ^ nb2[i];
    }
    *new_size = size;
    return res;
}

uint8_t *right_shift(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size) {
    uint8_t *a = calloc(size, 1);
    uint8_t *b = calloc(size, 1);
    uint8_t *one = calloc(size, 1);
    memcpy(a, nb1, size);
    memcpy(b, nb2, size);
    one[size - 1] = 1;

    while(is_zero(b, size) == false){
        if(is_zero(a, size)){
            break;
        }
        uint32_t tmp_size = 0;
        b = substraction(b, one, size, &tmp_size);
        b = add_extra_bytes(b, tmp_size, size);
        shift_right(a, size, 1);
    }
    *new_size = size;
    free(b);
    free(one);
    return discard_useless_bytes(a, size, new_size);
}

uint8_t *left_shift(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size) {
    uint8_t *a = calloc(size, 1);
    uint8_t *b = calloc(size, 1);
    uint8_t *one = calloc(size, 1);
    memcpy(a, nb1, size);
    memcpy(b, nb2, size);
    one[size - 1] = 1;

    while(is_zero(b, size) == false){
        if(is_zero(a, size)){
            break;
        }
        uint32_t tmp_size = 0;
        b = substraction(b, one, size, &tmp_size);
        b = add_extra_bytes(b, tmp_size, size);
        shift_left(a, size, 1);
    }
    *new_size = size;
    free(b);
    free(one);
    return discard_useless_bytes(a, size, new_size);
}

uint8_t *right_rotate(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size) {
    uint8_t *res = calloc(size, 1);
    uint32_t tmp_size = 0;
    uint8_t *nb_turn = get_nb_turn(nb2, size, &tmp_size);
    uint8_t *one = calloc(tmp_size, 1);
    one[tmp_size - 1] = 1;

    while(is_zero(nb_turn, tmp_size) == false) {
        uint8_t tmp = (nb1[size - 1] & 1) << 7;
        for (uint32_t i = 0; i < size; ++i) {
            res[i] = (nb1[i] >> 1) | tmp;
            tmp = (nb1[i] & 1) << 7;
        }
        uint32_t tmp_sub_size;
        nb_turn = substraction(nb_turn, one, tmp_size, &tmp_sub_size);
        nb_turn = add_extra_bytes(nb_turn, tmp_sub_size, tmp_size);
    }
    
    *new_size = size;
    free(nb_turn);
    free(one);
    return res;
}

uint8_t *left_rotate(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size) {
    uint8_t *res = calloc(size, 1);
    uint32_t tmp_size = 0;
    uint8_t *nb_turn = get_nb_turn(nb2, size, &tmp_size);
    uint8_t *one = calloc(tmp_size, 1);
    one[tmp_size - 1] = 1;

    while(is_zero(nb_turn, tmp_size) == false) {
        uint8_t tmp = (nb1[0] & 128) >> 7;
        for (uint32_t i = size - 1; i < size; ++i) {
            res[i] = (nb1[i] << 1) | tmp;
            tmp = (nb1[i] & 128) >> 7;
        }
        uint32_t tmp_sub_size;
        nb_turn = substraction(nb_turn, one, tmp_size, &tmp_sub_size);
        nb_turn = add_extra_bytes(nb_turn, tmp_sub_size, tmp_size);
    }
    
    *new_size = size;
    free(nb_turn);
    free(one);
    return res;
}

uint8_t *get_nb_turn(uint8_t *nb1, uint32_t size, uint32_t *new_size){
    uint32_t nb_bit = size * 8;
    uint8_t *nb_bit_ptr = calloc(4, 1);
    memcpy(nb_bit_ptr, &nb_bit, 4);
    for (uint32_t i = 0; i < 2; ++i){
        uint8_t tmp = nb_bit_ptr[i];
        nb_bit_ptr[i] = nb_bit_ptr[3 - i];
        nb_bit_ptr[3 - i] = tmp;
    }
    PRINT_UINT32(nb_bit_ptr);
    puts("");
    if(size > 4){
        nb_bit_ptr = add_extra_bytes(nb_bit_ptr, 4, size);
    } else if (size < 4) {
        nb1 = add_extra_bytes(nb1, size, 4);
        size = 4;
    }
    uint8_t *nb_turn = modulo(nb1, nb_bit_ptr, size, new_size);
    PRINT_UINT8(nb_turn);
    puts("");
    return nb_turn;
}