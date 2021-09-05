SRCS				= 	srcs/main.c \
						srcs/utils/utils.c \
						srcs/operators/utils.c \
						srcs/operators/addition.c \
						srcs/operators/multiplication.c \
						srcs/operators/substraction.c \
						srcs/operators/division.c \
						srcs/operators/modulo.c \
						srcs/operators/exponent.c \
						srcs/operators/comparator.c \
						srcs/operators/bitwise.c \
						srcs/node/node.c \
						srcs/converters/binary.c \
						srcs/converters/hexadecimal.c \

OBJS				= ${SRCS:.c=.o}

NAME				= ft_infinite

FLAGS				= -Wall -Wextra -Werror

all :				${NAME}

${NAME} :			${OBJS}
					gcc -o ${NAME} ${FLAGS} ${SRCS}

clean :				
					rm -rf ${OBJS}

fclean : 			clean
					rm -rf ${NAME}

re :				fclean all

.PHONY:				all clean fclean re