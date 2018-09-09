/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_expr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjoanna- <rjoanna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 11:50:04 by rjoanna-          #+#    #+#             */
/*   Updated: 2018/09/09 21:59:34 by rjoanna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stacks.h"

void	ft_add_el_to_nstack(int nbr, t_nbr **nbr_stack)
{
	t_nbr	*new;

	new = (t_nbr *)malloc(sizeof(t_nbr));
	new->nbr = nbr;
	new->prev = *nbr_stack;
	*nbr_stack = new;
	g_start_bracket = 0;
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

void	ft_add_el_to_ostack(t_op *new, t_op **op_stack, t_nbr **nbr_stack)
{
	if ((*op_stack) != NULL && (*op_stack)->oper == '(' && g_start_bracket)
		ft_add_el_to_nstack(0, nbr_stack);
	if (*nbr_stack == NULL)
		ft_add_el_to_nstack(0, nbr_stack);
	new->prev = *op_stack;
	*op_stack = new;
	if (new->oper == '(')
		g_start_bracket = 1;
}

int		eval_expr(char *str)
{
	t_op	*op_stack;
	t_nbr	*nbr_stack;
	t_op	*new;

	ft_make_p_nulls(&op_stack, &nbr_stack);
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
		{
			ft_add_el_to_nstack(ft_atoi(str), &nbr_stack);
			while (*str >= '0' && *str <= '9')
				str++;
			str -= (*str == ')' || ft_is_valid_operator(*str)) ? 1 : 0;
		}
		else if (ft_is_valid_operator(*str))
		{
			new = ft_create_t_op(*str);
			ft_operation_is_valid(&new, &op_stack, &nbr_stack);
		}
		else if (*str == '(' || *str == ')')
			ft_brackets_analyze(*str, &op_stack, &nbr_stack);
		str += (*str != '\0') ? 1 : 0;
	}
	return (ft_finalize_stack(&op_stack, &nbr_stack));
}
