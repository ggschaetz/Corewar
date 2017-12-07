/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arive-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:11:18 by arive-de          #+#    #+#             */
/*   Updated: 2017/11/29 18:17:48 by arive-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		first_param3(t_process **p, t_arena **arena, int val1)
{
	int res;

	res = 0;
	if ((*p)->size_arg[0] == 1)
		val1 = (*p)->r[val1 - 1];
	else if ((*p)->dir && !(*p)->ind)
		val1 = (short int)(*p)->value_arg[0];
	else
	{
		res = m0d((*p)->pc->prev_pc + (*p)->champ->vm_pos + m0d(val1, IDX_MOD),
																	MEM_SIZE);
		if (val1 == 65535)
			res = m0d(res, IDX_MOD);
		while (res < 0)
			res += MEM_SIZE;
		val1 = get_value_arena(arena, res, 1);
	}
	return (val1);
}

int		lldi(t_process **p, t_arena **arena, t_verb **v)
{
	int val1;
	int val2;
	int val3;
	int res;

	res = 0;
	arg_value(p, arena, 9);
	val1 = (*p)->value_arg[0];
	val2 = (*p)->value_arg[1];
	val3 = (*p)->value_arg[2];
	val1 = first_param3(p, arena, val1);
	if ((*p)->size_arg[1] == 1)
		val2 = (*p)->r[val2 - 1];
	else
		val2 = (short int)(*p)->value_arg[1];
	res = (*p)->pc->prev_pc + m0d(val1 & val2, MEM_SIZE);
	(*p)->r[val3 - 1] = get_value_arena(arena, res, 1);
	if ((*v)->op)
		three_params_verb(val1, val2, val3, p);
	return (0);
}
