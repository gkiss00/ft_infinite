#include "./../ft_infinite.h"

uint8_t     *substraction(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size)
{
    uint8_t x[size];
    uint8_t y[size];
    memset(x, 0, size);
    memcpy(x, nb1, size);
    memset(y, 0, size);
    memcpy(y, nb2, size);

    while (is_zero(y, size) == false)
    {
        // carry now contains common
        // set bits of x and y
        uint8_t borrow[size];
        memset(borrow, 0, size);
        for(uint32_t i = 0; i < size; ++i){
            borrow[i] = ~(x[i]) & y[i];
        }
 
        // Sum of bits of x and y where at
        // least one of the bits is not set
        for(uint32_t i = 0; i < size; ++i){
            x[i] = x[i] ^ y[i];
        }
 
        // Carry is shifted by one so that adding
        // it to x gives the required sum
        uint8_t rest = 0;
        for(int i = (int)((size) - 1); i >= 0; --i){
            y[i] = borrow[i] << 1 | rest;
            rest = 0;
            rest |= borrow[i] >> 7;
        }
    }
    uint8_t *res = calloc(size, 1);
    memcpy(res, x, size);
    res = discard_useless_bytes(res, size, new_size);
    return res;
}