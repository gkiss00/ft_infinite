#include "./../ft_infinite.h"

uint8_t     *exponent(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size) {
    uint8_t *a = calloc(size, 1);
    uint8_t *b = calloc(size, 1);
    uint8_t *one = calloc(size, 1);
    uint8_t *res = calloc(size, 1);
    memcpy(a, nb1, size);
    memcpy(b, nb2, size);
    one[size - 1] = 1;
    memcpy(res, a, size);
    *new_size = size;
    while(is_sup(b, one, size) == true) {
        printf("%d\n", *new_size);
        PRINT_UINT8(res);
        puts("\nmult");
        res = multiplication(res, a, *new_size, new_size);
        puts("add");
        a = add_extra_bytes(a, size, *new_size);
        uint32_t tmp_size = 0;
        b = substraction(b, one, size, &tmp_size);
        b = add_extra_bytes(b, tmp_size, size);
    }
    return discard_useless_bytes(res, *new_size, new_size);
}