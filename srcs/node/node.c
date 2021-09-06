#include "./../ft_infinite.h"

t_operator *new_operator(char *name, uint8_t *(*op)(uint8_t*, uint8_t*, uint32_t, uint32_t*)) {
    t_operator *operator;

    operator = malloc(sizeof(t_operator));
    if(operator == NULL)
        exit_error(MALLOC_ERROR);
    operator->name = name ? strdup(name) : NULL;
    operator->operator = op;
    operator->next = NULL;
    return (operator);
}

t_operator *operator_last(t_operator *operator) {
    while (operator && operator->next) {
        operator = operator->next;
    }
    return (operator);
}

void operator_add_back(t_operator **head, t_operator *new) {
    if (head != 0)
	{
		if (*head && new != 0)
			operator_last(*head)->next = new;
		else
			*head = new;
	}
}

t_converter *new_convertor(char *name, int modulo, uint8_t *(*op)(uint8_t*, uint32_t)) {
    t_converter *converter;

    converter = malloc(sizeof(t_converter));
    if(converter == NULL)
        exit_error(MALLOC_ERROR);
    converter->name = name ? strdup(name) : NULL;
    converter->converter = op;
    converter->modulo = modulo;
    converter->next = NULL;
    return (converter);
}

t_converter *convertor_last(t_converter *converter) {
    while (converter && converter->next) {
        converter = converter->next;
    }
    return (converter);
}

void convertor_add_back(t_converter **head, t_converter *new) {
    if (head != 0)
	{
		if (*head && new != 0)
			convertor_last(*head)->next = new;
		else
			*head = new;
	}
}