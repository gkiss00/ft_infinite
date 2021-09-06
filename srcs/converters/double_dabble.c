#include "./../ft_infinite.h"

// static void    print_nb(char *msg, uint8_t *nb, uint32_t size) {
//     printf("%s: ", msg);
    // for (uint32_t i = 0; i < size; ++i) {
    //     PRINT_UINT8(&nb[i]);
    //     printf(" ");
    // }
//     printf("\n");
// }

static void    print_decimal(uint8_t *nb, uint32_t size) {
    uint8_t tmp;
    char    base[10] = "0123456789";
    printf("decimal\n");
    for(uint32_t i = 0; i < size; ++i) {
        
        tmp = nb[i] >> 4;
        if(i == 0 && tmp == 0){}else{write(1, &base[tmp], 1);}
        tmp = (nb[i] << 4);
        tmp = tmp >> 4;
        write(1, &base[tmp], 1);
    }
    write(1, "\n", 1);
}

uint8_t *double_dabble(uint8_t *nb, uint32_t size, uint32_t *new_size) {
    uint32_t nb_turn = size * 8;
    uint32_t triple_size = size * 3;
    uint8_t *res = calloc(triple_size, 1);

    for (uint32_t i = 0; i < nb_turn; ++i) {
        // print_nb("res", res, triple_size);
        // print_nb("nb", nb, size);
        for(uint32_t k = triple_size - 1; k < triple_size; --k) {
            uint8_t tmp;
            tmp = 0;
            tmp = res[k] << 4;
            tmp >>= 4;
            if(tmp >= 5){
                uint32_t nb_tmp_size;
                uint8_t *nb_tmp = calloc(triple_size, 1);
                uint8_t *three = calloc(triple_size, 1);
                three[k] = 3;
                memcpy(nb_tmp, res, triple_size);
                nb_tmp = addition(nb_tmp, three, triple_size, &nb_tmp_size);
                nb_tmp = add_extra_bytes(nb_tmp, nb_tmp_size, triple_size);
                res = nb_tmp;
                // printf("ADD-3\n");
                // print_nb("res", res, triple_size);
                // print_nb("nb", nb, size);
                // tmp += 3;
                // res[k] >>= 4;
                // res[k] <<= 4;
                // res[k] |= tmp;
                // break ;
            }
            tmp = 0;
            tmp = res[k] >> 4;
            if(tmp >= 5){
                uint32_t nb_tmp_size;
                uint8_t *nb_tmp = calloc(triple_size, 1);
                uint8_t *three = calloc(triple_size, 1);
                three[k] = 3 << 4;
                memcpy(nb_tmp, res, triple_size);
                nb_tmp = addition(nb_tmp, three, triple_size, &nb_tmp_size);
                nb_tmp = add_extra_bytes(nb_tmp, nb_tmp_size, triple_size);
                res = nb_tmp;
                // printf("ADD-3\n");
                // print_nb("res", res, triple_size);
                // print_nb("nb", nb, size);
                // tmp += 3;
                // res[k] <<= 4;
                // res[k] >>= 4;
                // res[k] |= (tmp << 4);
                // break ;
            }
        }
        // printf("SHIFT\n");
        shift_left(res, triple_size, 1);
        res[triple_size - 1] |= (nb[0] & 128) >> 7;
        shift_left(nb, size, 1);
    }
    // print_nb("res", res, triple_size);
    // print_nb("nb", nb, size);
    res = discard_useless_bytes(res, triple_size, new_size);
    print_decimal(res, *new_size);
    return res;
}