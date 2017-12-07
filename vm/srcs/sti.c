/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arive-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:12:54 by arive-de          #+#    #+#             */
/*   Updated: 2017/11/29 18:19:54 by arive-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		second_param(t_process **p, t_arena **arena, int val2)
{
	int res;

	res = 0;
	if ((*p)->size_arg[1] == 1)
		val2 = (*p)->r[val2 - 1];
	else if ((*p)->dir && !(*p)->ind)
		val2 = (short int)(*p)->value_arg[1];
	else
	{
		res = m0d((*p)->pc->prev_pc + (*p)->champ->vm_pos + m0d(val2, IDX_MOD),
																	MEM_SIZE);
		while (res < 0)
			res += MEM_SIZE;
		val2 = get_value_arena(arena, res, 1);
	}
	return (val2);
}

int		sti(t_process **p, t_arena **arena, t_verb **v)
{
	int val1;
	int val2;
	int val3;
	int res;

	res = 0;
	arg_value(p, arena, 10);
	val1 = (*p)->value_arg[0];
	val2 = (*p)->value_arg[1];
	val3 = (*p)->value_arg[2];
	val2 = second_param(p, arena, val2);
	if ((*p)->size_arg[2] == 1)
		val3 = (*p)->r[val3 - 1];
	else
	{
		val3 = (short int)(*p)->value_arg[2];
	}
	res = m0d((*p)->pc->prev_pc + (*p)->champ->vm_pos +
										m0d(val2 + val3, IDX_MOD), MEM_SIZE);
	put_value_arena(p, arena, val1, res);
	if ((*v)->op)
		three_params_verb(val1, val2, val3, p);
	return (0);
}
