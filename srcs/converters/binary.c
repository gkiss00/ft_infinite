#include "./../ft_infinite.h"

static uint8_t find_char(uint8_t c, uint8_t *base_min, uint32_t size) {
    for (uint32_t i = 0; i < size; ++i) {
        if(c == base_min[i])
            return (uint8_t)i;
    }
    return size;
}

// return a binary key from a binary string
uint8_t *str_bin_to_bin(uint8_t *str, uint32_t size) {
    uint8_t base_min[2] = "01";
    uint32_t base_size = 2;
    uint8_t *res = calloc(size / 8, 1);

    if(res == NULL)
        return NULL;

    for (uint32_t i = size - 1; i < size; --i) {
        uint8_t tmp = find_char(str[i], base_min, base_size);
        if(tmp == base_size){
            free(res);
            return NULL;
        }
        res[i / 8] |=  tmp <<  (8 - (i % 8));
    }
    return res;
    
}
