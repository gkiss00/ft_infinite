#include "./../ft_infinite.h"


// something is wrong
uint8_t *multiplication(uint8_t *nb1, uint8_t *nb2, uint32_t size, uint32_t *new_size)
{
    uint32_t tmp_size = size * 2;
    uint8_t *a = calloc(tmp_size, 1);
    uint8_t *b = calloc(tmp_size, 1);
    uint8_t *res = calloc(tmp_size, 1);
    memcpy(&a[size], nb1, size);
    memcpy(&b[size], nb2, size);

    bool first = true;
    printf("oui\n");
    // While second number doesn't become 1
    while (is_zero(b, tmp_size) == false)
    {
        printf("non\n");
        // If second number becomes odd, add the first number to result
        if (b[tmp_size - 1] & 1)
        {
            uint32_t s = 0;
            printf("add\n");
            res = addition(res, a, tmp_size, &s);
            s = s + 1;
            uint8_t *tmptmp = calloc(s, 1);
            memcpy(&tmptmp[1], res, s);
            res = tmptmp;

            if(first){
                printf("firt\n");
                printf("tmp1 %d %d\n", s, tmp_size);
                uint8_t *tmp1 = calloc(s, 1);
                uint32_t d = tmp_size > s ? tmp_size : s;
                memcpy(tmp1, &a[d], s);
                free(a);
                a = tmp1;
                printf("tmp2\n");
                uint8_t *tmp2 = calloc(s, 1);
                memcpy(tmp2, &b[d], s);
                free(b);
                b = tmp2;

                first = false;
            } else {
                printf("then\n");
                uint8_t *tmp1 = calloc(s, 1);
                memcpy(&tmp1[s - tmp_size], a, tmp_size);
                free(a);
                a = tmp1;

                uint8_t *tmp2 = calloc(s, 1);
                memcpy(&tmp2[s - tmp_size], b, tmp_size);
                free(b);
                b = tmp2;
            }
            tmp_size = s;
        }
        printf("a: ");
        print_number_hexa(a, tmp_size);
        printf("\n");
        printf("b: ");
        print_number_hexa(b, tmp_size);
        printf("\n");
        // Double the first number and halve the second number
        shift_left(a, tmp_size, 1);
        shift_right(b, tmp_size, 1);
    }
    res = discard_useless_bytes(res, tmp_size, new_size);
    return res;
}