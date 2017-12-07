/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arive-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:13:48 by arive-de          #+#    #+#             */
/*   Updated: 2017/11/29 17:14:08 by arive-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		xor(t_process **p, t_arena **arena, t_verb **v)
{
	int val1;
	int val2;
	int val3;

	arg_value(p, arena, 7);
	val1 = (*p)->value_arg[0];
	val2 = (*p)->value_arg[1];
	val3 = (*p)->value_arg[2];
	val1 = (*p)->size_arg[0] == 1 ? (*p)->r[val1 - 1] : val1;
	val1 = (*p)->size_arg[0] == 2 ? get_value_arena(arena, val1, 1) : val1;
	val2 = (*p)->size_arg[1] == 1 ? (*p)->r[val2 - 1] : val2;
	val2 = (*p)->size_arg[1] == 2 ? get_value_arena(arena, val2, 1) : val2;
	if ((*v)->op)
		three_params_verb(val1, val2, val3, p);
	if (!((*p)->r[val3 - 1] = val1 ^ val2))
		(*p)->carry = 1;
	else
		(*p)->carry = 0;
	return (0);
}
