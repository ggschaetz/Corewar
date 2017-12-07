/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arive-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:09:50 by arive-de          #+#    #+#             */
/*   Updated: 2017/11/29 17:09:51 by arive-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		aff(t_process **p, t_arena **arena, t_verb **v)
{
	int val1;

	(*v)->base = 1;
	arg_value(p, arena, 15);
	val1 = (*p)->r[(*p)->value_arg[1] - 1] % 256;
	if ((*v)->op)
		one_param_verb(val1, p);
	return (0);
}
