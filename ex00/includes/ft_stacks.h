/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stacks.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjoanna- <rjoanna-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 11:50:44 by rjoanna-          #+#    #+#             */
/*   Updated: 2018/09/09 11:50:45 by rjoanna-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACKS_H
# define FT_STACKS_H

# include <stdlib.h>

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

#endif
