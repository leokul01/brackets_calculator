/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_expr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjoanna- <rjoanna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 11:50:04 by rjoanna-          #+#    #+#             */
/*   Updated: 2018/09/09 11:50:05 by rjoanna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stacks.h"
#include "ft_prototypes.h"

t_op	*ft_create_t_op(char oper)
{
	t_op	*new;

	new = (t_op *)malloc(sizeof(t_op));
	new->oper = oper;
	new->prev = NULL;
	if (oper == '+')
	{
		new->f = ft_sum;
		new->priority = 1;
	}
	else if (oper == '-')
	{
		new->f = ft_sub;
		new->priority = 1;
	}
	else if (oper == '*')
	{
		new->f = ft_mul;
		new->priority = 2;
	}
	else if (oper == '/')
	{
		new->f = ft_div;
		new->priority = 2;
	}
	else if (oper == '%')
	{
		new->f = ft_mod;
		new->priority = 2;
	}
	else
	{
		new->f = 0;
		new->priority = 0;
	}
	return (new);
}

int		ft_is_valid_operator(char op)
{
	if (op == '*' || op == '/' || op == '%' || op == '+' || op == '-')
		return (1);
	return (0);
}

void	ft_add_el_to_nstack(int nbr, t_nbr **nbr_stack)
{
	t_nbr	*new;

	new = (t_nbr *)malloc(sizeof(t_nbr));
	new->nbr = nbr;
	new->prev = *nbr_stack;
	*nbr_stack = new;
}

int		ft_pull_from_nstack(t_nbr **nbr_stack)
{
	int		nbr;
	t_nbr	*tmp;

	nbr = (*nbr_stack)->nbr;
	tmp = (*nbr_stack)->prev;
	free(*nbr_stack);
	*nbr_stack = tmp;
	return (nbr);
}

void	ft_pull_from_ostack(t_op **op_stack)
{
	t_op	*tmp;

	tmp = (*op_stack)->prev;
	free(*op_stack);
	*op_stack = tmp;
}

void	ft_add_el_to_ostack(t_op *new, t_op **op_stack)
{
	new->prev = *op_stack;
	*op_stack = new;
}

int		eval_expr(char *str)
{
	t_op	*op_stack;
	t_nbr	*nbr_stack;
	t_op	*new;
	int		nbr;

	op_stack = NULL;
	nbr_stack = NULL;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
		{
			ft_add_el_to_nstack(ft_atoi(str), &nbr_stack);
			while (*str >= '0' && *str <= '9')
				str++;
			str -= (*str == ')') ? 1 : 0;
		}
		else if (ft_is_valid_operator(*str))
		{
			new = ft_create_t_op(*str);
			if (op_stack == NULL)
				ft_add_el_to_ostack(new, &op_stack);
			else if (op_stack->priority < new->priority)
				ft_add_el_to_ostack(new, &op_stack);
			else if (op_stack->priority > new->priority)
			{
				nbr = op_stack->f(ft_pull_from_nstack(&nbr_stack),
						ft_pull_from_nstack(&nbr_stack));
				ft_pull_from_ostack(&op_stack);
				ft_add_el_to_nstack(nbr, &nbr_stack);
				if (op_stack && op_stack->priority == new->priority)
				{
					nbr = op_stack->f(ft_pull_from_nstack(&nbr_stack),
							ft_pull_from_nstack(&nbr_stack));
					ft_pull_from_ostack(&op_stack);
					ft_add_el_to_nstack(nbr, &nbr_stack);
				}
				ft_add_el_to_ostack(new, &op_stack);
			}
			else
			{
				nbr = op_stack->f(ft_pull_from_nstack(&nbr_stack),
						ft_pull_from_nstack(&nbr_stack));
				ft_pull_from_ostack(&op_stack);
				ft_add_el_to_nstack(nbr, &nbr_stack);
				ft_add_el_to_ostack(new, &op_stack);
			}
			str++;
		}
		else if (*str == '(')
		{
			new = ft_create_t_op(*str);
			ft_add_el_to_ostack(new, &op_stack);
		}
		else if (*str == ')')
		{
			while (op_stack->oper != '(')
			{
				nbr = op_stack->f(ft_pull_from_nstack(&nbr_stack),
						ft_pull_from_nstack(&nbr_stack));
				ft_pull_from_ostack(&op_stack);
				ft_add_el_to_nstack(nbr, &nbr_stack);
			}
			ft_pull_from_ostack(&op_stack);
		}
		str += (*str != '\0') ? 1 : 0;
	}
	while (nbr_stack)
	{
		nbr = op_stack->f(ft_pull_from_nstack(&nbr_stack),
				ft_pull_from_nstack(&nbr_stack));
		if (nbr_stack != NULL)
			ft_add_el_to_nstack(nbr, &nbr_stack);
		ft_pull_from_ostack(&op_stack);
	}
	return (nbr);
}
