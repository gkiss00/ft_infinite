#include "./../ft_infinite.h"

uint8_t *superior(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size)
{
    uint8_t *res = calloc(1, 1);
    *new_size = 1;
    for (uint32_t i = 0; i < size; ++i) {
        if(nb1[i] > nb2[i]){
            *res = 1;
            break;
        } else if (nb1[i] < nb2[i]) {
            break;
        }
    }
    return res;
}

uint8_t *inferior(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size)
{
    uint8_t *res = calloc(1, 1);
    *new_size = 1;
    for (uint32_t i = 0; i < size; ++i) {
        if(nb1[i] < nb2[i]){
            *res = 1;
            break;
        } else if (nb1[i] > nb2[i]) {
            break;
        }
    }
    return res;
}

uint8_t *equal(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size)
{
    uint8_t *res = calloc(1, 1);
    *new_size = 1;
    *res = 1;
    for (uint32_t i = 0; i < size; ++i) {
        if(nb1[i] != nb2[i]){
            *res = 0;
            break;
        }
    }
    return res;
}

uint8_t *not_equal(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size)
{
    uint8_t *res = calloc(1, 1);
    *new_size = 1;
    for (uint32_t i = 0; i < size; ++i) {
        if(nb1[i] != nb2[i]){
            *res = 1;
            break;
        }
    }
    return res;
}

uint8_t *superior_or_equal(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size)
{
    uint8_t *res = calloc(1, 1);
    uint8_t *tmp1 = superior(nb1, nb2, size, new_size);
    uint8_t *tmp2 = equal(nb1, nb2, size, new_size);
    *res = *tmp1 | *tmp2;
    free(tmp1);
    free(tmp2);
    return res;
}

uint8_t *inferior_or_equal(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size)
{
    uint8_t *res = calloc(1, 1);
    uint8_t *tmp1 = inferior(nb1, nb2, size, new_size);
    uint8_t *tmp2 = equal(nb1, nb2, size, new_size);
    *res = *tmp1 | *tmp2;
    free(tmp1);
    free(tmp2);
    return res;
}