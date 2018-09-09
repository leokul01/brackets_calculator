/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_expr_addit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjoanna- <rjoanna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 20:07:53 by rjoanna-          #+#    #+#             */
/*   Updated: 2018/09/09 21:59:15 by rjoanna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stacks.h"

void	init_t_op(t_op *new, int (*f)(int a, int b), int pr)
{
	new->f = f;
	new->priority = pr;
}

int		ft_is_valid_operator(char op)
{
	if (op == '*' || op == '/' || op == '%' || op == '+' || op == '-')
		return (1);
	return (0);
}

void	ft_op_is_valid_eq(int nbr, t_op **new, t_op **op_stack,
	t_nbr **nbr_stack)
{
	ft_pull_from_ostack(op_stack);
	ft_add_el_to_nstack(nbr, nbr_stack);
	ft_add_el_to_ostack((*new), op_stack, nbr_stack);
}

void	ft_operation_is_valid(t_op **new, t_op **op_stack,
	t_nbr **nbr_stack)
{
	int		nbr;

	if (*op_stack == NULL || (*op_stack)->priority < (*new)->priority)
		ft_add_el_to_ostack((*new), op_stack, nbr_stack);
	else if ((*op_stack)->priority > (*new)->priority)
	{
		nbr = (*op_stack)->f(ft_pull_from_nstack(nbr_stack),
				ft_pull_from_nstack(nbr_stack));
		ft_pull_from_ostack(op_stack);
		ft_add_el_to_nstack(nbr, nbr_stack);
		if ((*op_stack) && (*op_stack)->priority == (*new)->priority)
		{
			nbr = (*op_stack)->f(ft_pull_from_nstack(nbr_stack),
					ft_pull_from_nstack(nbr_stack));
			ft_pull_from_ostack(op_stack);
			ft_add_el_to_nstack(nbr, nbr_stack);
		}
		ft_add_el_to_ostack((*new), op_stack, nbr_stack);
	}
	else
	{
		nbr = (*op_stack)->f(ft_pull_from_nstack(nbr_stack),
				ft_pull_from_nstack(nbr_stack));
		ft_op_is_valid_eq(nbr, new, op_stack, nbr_stack);
	}
}

void	ft_brackets_analyze(char c, t_op **op_stack, t_nbr **nbr_stack)
{
	t_op	*new;
	int		nbr;

	if (c == '(')
	{
		new = ft_create_t_op(c);
		ft_add_el_to_ostack(new, op_stack, nbr_stack);
	}
	else if (c == ')')
	{
		while ((*op_stack)->oper != '(')
		{
			nbr = (*op_stack)->f(ft_pull_from_nstack(nbr_stack),
					ft_pull_from_nstack(nbr_stack));
			ft_pull_from_ostack(op_stack);
			ft_add_el_to_nstack(nbr, nbr_stack);
		}
		ft_pull_from_ostack(op_stack);
	}
}
