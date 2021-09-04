#include "./../ft_infinite.h"

static uint8_t find_char(uint8_t c, uint8_t *base_min, uint8_t *base_maj, uint32_t size) {
    for (uint32_t i = 0; i < size; ++i) {
        if(c == base_min[i] || c == base_maj[i])
            return (uint8_t)i;
    }
    return 16;
}

// return a binary key from a hex string
uint8_t *str_to_hex(uint8_t *str, uint32_t size) {
    uint8_t base_min[16] = "0123456789abcdef";
    uint8_t base_maj[16] = "0123456789ABCDEF";
    uint8_t *res = calloc(size / 2, 1);

    if(res == NULL)
        return NULL;

    for (uint32_t i = size - 1; i < size; --i) {
        uint8_t tmp = find_char(str[i], base_min, base_maj, 16);
        if(tmp == 16)
            return NULL;
        res[i / 2] |= tmp << (4 * (1 - (i % 2))); // 0001
    }
    return res;
    
}