/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arive-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:17:32 by arive-de          #+#    #+#             */
/*   Updated: 2017/11/30 21:18:31 by mkantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		zjmp(t_process **p, t_arena **arena, t_verb **v)
{
	int idx;

	arg_value(p, arena, 8);
	idx = (*p)->value_arg[0];
	if ((*v)->op)
		one_param_verb((*p)->value_arg[0], p);
	if ((*p)->carry == 1)
	{
		if ((*p)->pc->prev_pc + idx < 0)
			(*p)->pc->cur_pc = MEM_SIZE + ((*p)->pc->prev_pc - (ABS(idx)));
		else
			(*p)->pc->cur_pc = (*p)->pc->prev_pc + (*p)->value_arg[0];
		(*p)->pc->prev_pc = (*p)->pc->cur_pc;
	}
	return (0);
}
