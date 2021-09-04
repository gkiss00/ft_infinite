#include "./ft_infinite.h"

static t_command *init_cmd(){
    t_command *head = new_command((uint8_t*)"+", &addition);
    command_add_back(&head, new_command((uint8_t*)"-", &substraction));
    command_add_back(&head, new_command((uint8_t*)"*", &multiplication));
    command_add_back(&head, new_command((uint8_t*)"/", &division));
    command_add_back(&head, new_command((uint8_t*)"%", &modulo));
    command_add_back(&head, new_command((uint8_t*)"^", &exponent));
    command_add_back(&head, new_command((uint8_t*)"<", &inferior));
    command_add_back(&head, new_command((uint8_t*)">", &superior));
    command_add_back(&head, new_command((uint8_t*)"<=", &inferior_or_equal));
    command_add_back(&head, new_command((uint8_t*)">=", &superior_or_equal));
    command_add_back(&head, new_command((uint8_t*)"==", &equal));
    command_add_back(&head, new_command((uint8_t*)"!=", &not_equal));
    return head;
}

static void hub(t_command *cmd, char *arg, uint8_t *nb1, uint8_t *nb2, uint32_t size){
    uint8_t *res;
    uint32_t new_size = 0;
    while(cmd != NULL){
        if(strcmp(arg, (char*)cmd->name) == 0){
            res = cmd->operator(nb1, nb2, size, &new_size);
            break;
        }
        cmd = cmd->next;
    }
    if(cmd == NULL)
        exit_error(CMD_ERROR);
    for (uint32_t i = 0; i < new_size; ++i) {
        printf("%02x", res[i]);
    }
    printf("\n");
}

int main(int argc, char **argv){
    t_command *cmd = init_cmd();
    if(argc < 4)
        exit_error(INPUT_ERROR);
    if(strlen(argv[1]) % 2 == 1 || strlen(argv[3]) % 2 == 1)
        exit_error(ODD_ERROR);
    uint32_t nb1_size = (uint32_t)strlen(argv[1]) / 2;
    uint32_t nb2_size = (uint32_t)strlen(argv[3]) / 2;
    uint32_t size = nb1_size > nb2_size ? nb1_size : nb2_size;

    uint8_t *nb1 = str_to_hex((uint8_t*)argv[1], (uint32_t)strlen(argv[1]));
    uint8_t *nb2 = str_to_hex((uint8_t*)argv[3], (uint32_t)strlen(argv[3]));
    if(nb1 == NULL || nb2 == NULL)
        exit_error(INPUT_ERROR);
    nb1 = add_extra_bytes(nb1, nb1_size, size);
    nb2 = add_extra_bytes(nb2, nb2_size, size);
    if(nb1 == NULL || nb2 == NULL)
        exit_error(MALLOC_ERROR);

    hub(cmd, argv[2], nb1, nb2, size);
}