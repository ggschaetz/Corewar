/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arive-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:12:39 by arive-de          #+#    #+#             */
/*   Updated: 2017/11/29 18:18:29 by arive-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		st(t_process **p, t_arena **arena, t_verb **v)
{
	int val1;
	int val2;
	int res;

	res = 0;
	arg_value(p, arena, 2);
	val1 = (*p)->value_arg[0];
	val2 = (*p)->value_arg[1];
	if ((*p)->size_arg[1] == 2)
	{
		res = m0d((*p)->pc->prev_pc + (*p)->champ->vm_pos + m0d(val2, IDX_MOD),
																	MEM_SIZE);
		while (res < 0)
			res += MEM_SIZE;
		put_value_arena(p, arena, val1, res);
	}
	else
		(*p)->r[val2 - 1] = (*p)->r[val1 - 1];
	if ((*v)->op)
		two_params_verb(val1, val2, p);
	return (0);
}
