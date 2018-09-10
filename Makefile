# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rjoanna- <rjoanna-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/09 11:50:30 by rjoanna-          #+#    #+#              #
#    Updated: 2018/09/10 10:32:20 by rjoanna-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		eval_expr
FLAGS		=		-Wall -Wextra -Werror
OPTIONS		=		-c -I./includes/
SRC			=		main.c srcs/calc_funcs.c srcs/eval_expr.c \
srcs/ft_putchar.c srcs/ft_putnbr.c srcs/ft_atoi.c \
srcs/eval_expr_addit.c srcs/eval_expr_addit2.c
OBJ			=		main.o calc_funcs.o eval_expr.o ft_putchar.o \
ft_putnbr.o ft_atoi.o eval_expr_addit.o eval_expr_addit2.o

all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(OPTIONS) $(SRC)
	gcc $(FLAGS) $(OBJ) -o $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
