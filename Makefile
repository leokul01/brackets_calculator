NAME		=		eval_expr
FLAGS		=		-Wall -Wextra -Werror
OPTIONS		=		-c -I./includes/
SRC			=		main.c srcs/calc_funcs.c srcs/eval_expr.c \
srcs/ft_putchar.c srcs/ft_putnbr.c srcs/ft_atoi.c
OBJ			=		main.o calc_funcs.o eval_expr.o ft_putchar.o \
ft_putnbr.o ft_atoi.o

all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(OPTIONS) $(SRC)
	gcc $(FLAGS) $(OBJ) -o $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
