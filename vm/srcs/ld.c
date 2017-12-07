/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arive-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:09:29 by arive-de          #+#    #+#             */
/*   Updated: 2017/11/29 18:09:26 by arive-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		ld(t_process **p, t_arena **arena, t_verb **v)
{
	int val1;
	int val2;
	int res;

	res = 0;
	arg_value(p, arena, 1);
	val1 = (*p)->value_arg[0];
	val2 = (*p)->value_arg[1];
	if ((*p)->size_arg[0] == 2)
	{
		res = m0d((*p)->pc->prev_pc + (*p)->champ->vm_pos + m0d(val1, IDX_MOD),
																	MEM_SIZE);
		if (val1 == 65535)
			res = m0d(res, IDX_MOD);
		while (res < 0)
			res += MEM_SIZE;
		res = get_value_arena(arena, res, 1);
		(*p)->r[val2 - 1] = res;
	}
	else
		(*p)->r[val2 - 1] = val1;
	(*p)->carry = (*p)->r[val2 - 1] == 0 ? 1 : 0;
	if ((*v)->op)
		two_params_verb((*p)->r[val2 - 1], val2, p);
	return (0);
}
