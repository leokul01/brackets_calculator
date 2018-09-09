/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stacks.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjoanna- <rjoanna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 11:50:44 by rjoanna-          #+#    #+#             */
/*   Updated: 2018/09/09 21:59:05 by rjoanna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACKS_H
# define FT_STACKS_H

# include <stdlib.h>

int				g_start_bracket;

typedef struct	s_op
{
	char			oper;
	int				(*f)(int a, int b);
	int				priority;
	struct s_op		*prev;
}				t_op;

typedef struct	s_nbr
{
	int				nbr;
	struct s_nbr	*prev;
}				t_nbr;

void			init_t_op(t_op *new, int (*f)(int a, int b), int pr);
int				ft_is_valid_operator(char op);
void			ft_op_is_valid_eq(int nbr, t_op **new, t_op **op_stack,
					t_nbr **nbr_stack);
void			ft_operation_is_valid(t_op **new, t_op **op_stack,
					t_nbr **nbr_stack);
void			ft_brackets_analyze(char c, t_op **op_stack,
					t_nbr **nbr_stack);
t_op			*ft_create_t_op(char oper);
void			ft_make_p_nulls(t_op **op_stack, t_nbr **nbr_stack);
int				ft_finalize_stack(t_op **op_stack, t_nbr **nbr_stack);
int				eval_expr(char *str);
int				ft_sum(int a, int b);
int				ft_sub(int a, int b);
int				ft_mul(int a, int b);
int				ft_div(int a, int b);
int				ft_mod(int a, int b);
int				ft_atoi(char *str);
void			ft_putchar(char c);
void			ft_putnbr(int nb);
void			ft_add_el_to_nstack(int nbr, t_nbr **nbr_stack);
int				ft_pull_from_nstack(t_nbr **nbr_stack);
void			ft_pull_from_ostack(t_op **op_stack);
void			ft_add_el_to_ostack(t_op *new, t_op **op_stack,
					t_nbr **nbr_stack);
#endif
