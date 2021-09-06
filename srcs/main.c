#include "./ft_infinite.h"

static char *in = NULL, *out = NULL;

static struct option long_options[] =
{
    /* These options set a flag. */
    {"in",  required_argument,  0, 'a'}, // BIN | HEX | 255
    {"out", required_argument,  0, 'b'}, // BIN | HEX | 255 | DEC
    {0, 0, 0, 0}
};

static void print_usage(){
    fprintf(stderr, "usage:\n");
    fprintf(stderr, "\t./ft_infinite <nb1> <operator> <nb2>\n");
    fprintf(stderr, "options:\n");
    fprintf(stderr, "\t-in\t<BIN | HEX | 255>\n");
    fprintf(stderr, "\t-out\t<BIN | HEX | 255 | DEC>\n");
}

static t_converter *init_converters(){
    t_converter *head = new_convertor("HEX", 2, &str_hex_to_bin);
    convertor_add_back(&head, new_convertor("BIN", 8, &str_bin_to_bin));
    convertor_add_back(&head, new_convertor("255", 3, &str_255_to_bin));
    return head;
}

static t_operator *init_operators(){
    t_operator *head = new_operator("+", &addition);
    operator_add_back(&head, new_operator("-", &substraction));
    operator_add_back(&head, new_operator("*", &multiplication));
    operator_add_back(&head, new_operator("/", &division));
    operator_add_back(&head, new_operator("%", &modulo));
    operator_add_back(&head, new_operator("**", &exponent));
    operator_add_back(&head, new_operator("<", &inferior));
    operator_add_back(&head, new_operator(">", &superior));
    operator_add_back(&head, new_operator("<=", &inferior_or_equal));
    operator_add_back(&head, new_operator(">=", &superior_or_equal));
    operator_add_back(&head, new_operator("==", &equal));
    operator_add_back(&head, new_operator("!=", &not_equal));
    operator_add_back(&head, new_operator("~", &not));
    operator_add_back(&head, new_operator("&", &and));
    operator_add_back(&head, new_operator("|", &or));
    operator_add_back(&head, new_operator("^", &xor));
    operator_add_back(&head, new_operator(">>", &right_shift));
    operator_add_back(&head, new_operator("<<", &left_shift));
    operator_add_back(&head, new_operator(">>>", &right_rotate));
    operator_add_back(&head, new_operator("<<<", &left_rotate));
    return head;
}

static uint32_t calc(t_operator *cmd, char *arg, uint8_t *nb1, uint8_t *nb2, uint32_t size, uint8_t **res_ptr){
    uint8_t *res;
    uint32_t new_size = 0;
    while(cmd != NULL){
        if(strcmp(arg, cmd->name) == 0){
            res = cmd->operator(nb1, nb2, size, &new_size);
            break;
        }
        cmd = cmd->next;
    }
    if(cmd == NULL) {
        fprintf(stderr, "ft_infinite: operator %s not found\n", arg);
        print_usage();
        exit(EXIT_FAILURE);
    }
    *res_ptr = res;
    return new_size;
}


static void output(uint8_t *nb, uint32_t size){
    if (out == NULL || strcmp(out, "HEX") == 0){
        for (uint32_t i = 0; i < size; ++i) {
            printf("%02x", nb[i]);
        }
    } else if (strcmp(out, "BIN") == 0) {
        for (uint32_t i = 0; i < size; ++i) {
            PRINT_UINT8(&nb[i]);
            printf(" ");
        }
    } else if (strcmp(out, "255") == 0) {
        for (uint32_t i = 0; i < size; ++i) {
            printf("%03d", nb[i]);
        }
    } else if (strcmp(out, "DEC") == 0) {
        uint32_t new_new_size = 0;
        double_dabble(nb, size, &new_new_size);
    } else {
        fprintf(stderr, "ft_infinite: conversion %s not found\n", out);
        print_usage();
        exit(EXIT_FAILURE);
    }
    printf("\n");
}

static char *fill_with_zero(char *arg, int modulo) {
    int     len = strlen(arg);
    char    *res = calloc(len + (len % modulo == 0 ? 0 : (modulo - (len % modulo))) + 1, 1);

    if(res == NULL)
        return res;

    memset(res, '0', len + (len % modulo == 0 ? 0 : (modulo - (len % modulo))));
    memcpy(&res[(len % modulo == 0 ? 0 : (modulo - (len % modulo)))], arg, len);
    return res;
}

static uint32_t convert(t_converter *converter, char *arg1, char *arg2, uint8_t **nb1_addr, uint8_t **nb2_addr){
    int     size = 0;
    int     len_arg1 = strlen(arg1);
    int     len_arg2 = strlen(arg2);
    uint8_t *nb1 = NULL;
    uint8_t *nb2 = NULL;
    while(converter != NULL) {
        if(in == NULL || strcmp(in, converter->name) == 0){
            // fill with 0 to get a correct size
            arg1 = fill_with_zero(arg1, converter->modulo);
            arg2 = fill_with_zero(arg2, converter->modulo);
            if(arg1 == NULL || arg2 == NULL){
                exit_error(MALLOC_ERROR);
            }
            // get nb size
            len_arg1 = strlen(arg1) / converter->modulo;
            len_arg2 = strlen(arg2) / converter->modulo;
            size = len_arg1 > len_arg2 ? len_arg1 : len_arg2;
            // convert
            nb1 = converter->converter((uint8_t*)arg1, (uint32_t)strlen(arg1));
            nb2 = converter->converter((uint8_t*)arg2, (uint32_t)strlen(arg2));
            break;
        }
        converter = converter->next;
    }
    if(converter == NULL) {
        fprintf(stderr, "ft_infinite: conversion %s not found\n", in);
        print_usage();
        exit(EXIT_FAILURE);
    }
    if(nb1 == NULL || nb2 == NULL){
        fprintf(stderr, "ft_infinite: a problem happenned during the conversion\n");
        exit(EXIT_FAILURE);
    }
    // fill with \0
    nb1 = add_extra_bytes(nb1, (uint32_t)len_arg1, (uint32_t)size);
    nb2 = add_extra_bytes(nb2, (uint32_t)len_arg2, (uint32_t)size);
    if(nb1 == NULL || nb2 == NULL){
        exit_error(MALLOC_ERROR);
    }
    *nb1_addr = nb1;
    *nb2_addr = nb2;
    return (uint32_t)size;
}

static char **parsing(int argc, char**argv){
    int c;
    int option_index = 0;
    while ((c = getopt_long_only(argc, argv, "", long_options, &option_index)) != EOF)
    {
        switch (c)
        {
        case 0:
            break;
        case 'a':
            in = optarg;
            break;
        case 'b':
            out = optarg;
            break;
        case '?':
            print_usage();
            exit(EXIT_FAILURE);
        default:
            print_usage();
            exit(EXIT_FAILURE);
        }
    }
    if(argc - optind != 3){
        fprintf(stderr, "ft_infinite: 3 arguments required\n");
        print_usage();
        exit(EXIT_FAILURE);
    }
    return (&argv[optind]);
}

int main(int argc, char **argv){
    uint8_t *nb1;
    uint8_t *nb2;
    uint8_t *res;
    uint32_t size;
    uint32_t new_size;
    t_operator *operators = init_operators();
    t_converter *convertors = init_converters();

    if(argc == 1){
        print_usage();
        exit(EXIT_FAILURE);
    }
    argv = parsing(argc, argv);
    size = convert(convertors, argv[0], argv[2], &nb1, &nb2);
    new_size = calc(operators, argv[1], nb1, nb2, size, &res);
    output(res, new_size);
}