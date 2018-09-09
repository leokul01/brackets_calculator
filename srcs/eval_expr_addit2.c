/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_expr_addit2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjoanna- <rjoanna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 20:00:13 by rjoanna-          #+#    #+#             */
/*   Updated: 2018/09/09 21:59:21 by rjoanna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stacks.h"

t_op	*ft_create_t_op(char oper)
{
	t_op	*new;

	new = (t_op *)malloc(sizeof(t_op));
	new->oper = oper;
	new->prev = NULL;
	if (oper == '+')
		init_t_op(new, ft_sum, 1);
	else if (oper == '-')
		init_t_op(new, ft_sub, 1);
	else if (oper == '*')
		init_t_op(new, ft_mul, 2);
	else if (oper == '/')
		init_t_op(new, ft_div, 2);
	else if (oper == '%')
		init_t_op(new, ft_mod, 2);
	else
		init_t_op(new, 0, 0);
	return (new);
}

void	ft_make_p_nulls(t_op **op_stack, t_nbr **nbr_stack)
{
	*op_stack = NULL;
	*nbr_stack = NULL;
}

int		ft_finalize_stack(t_op **op_stack, t_nbr **nbr_stack)
{
	int nbr;
	int tmp;

	if (*op_stack == NULL && *nbr_stack == NULL)
		return (0);
	while (*nbr_stack)
	{
		tmp = ft_pull_from_nstack(nbr_stack);
		if (*nbr_stack == NULL || *op_stack == NULL)
			return (tmp);
		nbr = (*op_stack)->f(tmp, ft_pull_from_nstack(nbr_stack));
		if (*nbr_stack != NULL)
			ft_add_el_to_nstack(nbr, nbr_stack);
		ft_pull_from_ostack(op_stack);
	}
	return (nbr);
}
