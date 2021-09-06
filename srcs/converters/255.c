#include "./../ft_infinite.h"

static uint8_t find_char(uint8_t c, uint8_t *base, uint32_t size) {
    for (uint32_t i = 0; i < size; ++i) {
        if(c == base[i])
            return (uint8_t)i;
    }
    return size;
}

uint8_t *str_255_to_bin(uint8_t *str, uint32_t size){
    printf("%s\n", (char*)str);
    uint8_t base_min[10] = "0123456789";
    uint32_t base_size = 10;
    uint8_t *res = calloc(size / 3, 1);

    if(res == NULL)
        return NULL;

    int int_tmp = 0;
    for (uint32_t i = 0; i < size; ++i){
        uint8_t tmp = find_char(str[i], base_min, base_size);
        if(tmp == base_size){
            free(res);
            return NULL;
        }
        if(i % 3 == 0){
            int_tmp = 0;
        }
        int_tmp += (int)tmp * (pow(10, 2 - (i % 3)));
        if(i % 3 == 2 && int_tmp > 255) {
            free(res);
            return NULL;
        } else if (i % 3 == 2) {
            memcpy(&res[i / 3], &int_tmp, 1);
        }
    }
    puts("");
    return res;
}