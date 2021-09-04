#include "./../ft_infinite.h"

uint8_t *add_extra_bytes(uint8_t *nb, uint32_t size, uint32_t new_size)
{
    if (size == new_size || new_size < size)
        return nb;
    uint8_t *res = calloc(new_size, 1);
    memcpy(&res[new_size - size], nb, size);
    free(nb);
    return res;
}

uint8_t     *discard_useless_bytes(uint8_t *nb, uint32_t size, uint32_t *new_size)
{
    uint32_t c = 0;

    for (uint32_t i = 0; i < size; ++i) {
        if(nb[i] != 0)
            break;
        ++c;
    }
    *new_size = size -c;
    uint8_t *res = calloc(size - c, 1);
    memcpy(res, &nb[c], size -c);
    return res;
}

bool is_zero(uint8_t *nb1, uint32_t size)
{
    for(uint32_t i = 0; i < size; ++i){
        if(nb1[i] != 0)
            return false;
    }
    return true;
}

bool is_sup(uint8_t *nb1, uint8_t *nb2, uint32_t size)
{
    for(uint32_t i = 0; i < size; ++i){
        if(nb1[i] > nb2[i])
            return true;
        if(nb1[i] < nb2[i])
            return false;
    }
    return false;
}

bool is_inf(uint8_t *nb1, uint8_t *nb2, uint32_t size)
{
    for(uint32_t i = 0; i < size; ++i){
        if(nb1[i] < nb2[i])
            return true;
        if(nb1[i] > nb2[i])
            return false;
    }
    return false;
}

bool is_sup_or_equal(uint8_t *nb1, uint8_t *nb2, uint32_t size)
{
    for(uint32_t i = 0; i < size; ++i){
        if(nb1[i] > nb2[i])
            return true;
        if(nb1[i] < nb2[i])
            return false;
    }
    return true;
}

bool is_inf_or_equal(uint8_t *nb1, uint8_t *nb2, uint32_t size)
{
    for(uint32_t i = 0; i < size; ++i){
        if(nb1[i] < nb2[i])
            return true;
        if(nb1[i] > nb2[i])
            return false;
    }
    return true;
}

void shift_left(uint8_t *number, uint32_t size, uint32_t bit) {
    uint8_t rest = 0;
    uint8_t cpy[size];
    memcpy(cpy, number, size);

    for(int i = (int)((size) - 1); i >= 0; --i){
        number[i] = number[i] << bit | rest;
        rest = 0;
        rest |= cpy[i] >> (8 - bit);
    }
}

void shift_right(uint8_t *number, uint32_t size, uint32_t bit) {
    uint8_t rest = 0;
    uint8_t cpy[size];
    memcpy(cpy, number, size);

    for(int i = 0; i < (int)size; ++i){
        number[i] = number[i] >> bit | rest;
        rest = 0;
        rest |= cpy[i] << (8 - bit);
    }
}