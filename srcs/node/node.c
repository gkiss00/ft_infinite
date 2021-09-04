#include "./../ft_infinite.h"

t_command *new_command(uint8_t *name, uint8_t *(*operator)(uint8_t*, uint8_t*, uint32_t, uint32_t*)) {
    t_command *command;

    command = malloc(sizeof(t_command));
    if(command == NULL)
        exit_error(MALLOC_ERROR);
    command->name = name ? (uint8_t*)strdup((char*)name): NULL;
    command->operator = operator;
    command->next = NULL;
    return (command);
}

t_command *command_last(t_command *command) {
    while (command && command->next) {
        command = command->next;
    }
    return (command);
}

void command_add_back(t_command **head, t_command *new) {
    if (head != 0)
	{
		if (*head && new != 0)
			command_last(*head)->next = new;
		else
			*head = new;
	}
}