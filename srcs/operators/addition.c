#include "./../ft_infinite.h"

uint8_t     *addition(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size)
{
    uint32_t double_size = size * 2;
    uint8_t x[double_size];
    uint8_t y[double_size];
    memset(x, 0, double_size);
    memcpy(&x[size], nb1, size);
    memset(y, 0, double_size);
    memcpy(&y[size], nb2, size);

    while (is_zero(y, double_size) == false)
    {
        // carry now contains common
        // set bits of x and y
        uint8_t carry[double_size];
        memset(carry, 0, double_size);
        for(uint32_t i = 0; i < double_size; ++i){
            carry[i] = x[i] & y[i];
        }
 
        // Sum of bits of x and y where at
        // least one of the bits is not set
        for(uint32_t i = 0; i < double_size; ++i){
            x[i] = x[i] ^ y[i];
        }
 
        // Carry is shifted by one so that adding
        // it to x gives the required sum
        uint8_t rest = 0;
        for(int i = (int)((double_size) - 1); i >= 0; --i){
            y[i] = carry[i] << 1 | rest;
            rest = 0;
            rest |= carry[i] >> 7;
        }
    }
    uint8_t *res = calloc(double_size, 1);
    memcpy(res, x, double_size);
    res = discard_useless_bytes(res, double_size, new_size);
    return res;
}