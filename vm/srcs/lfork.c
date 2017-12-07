/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arive-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:09:12 by arive-de          #+#    #+#             */
/*   Updated: 2017/11/29 17:09:15 by arive-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

t_process	*op_lspe(t_process **p, t_process **tmp, t_arena **arena,
		t_verb **v)
{
	int idx;

	arg_value(tmp, arena, 14);
	idx = (*tmp)->value_arg[0];
	if ((*v)->op)
		one_param_verb((*tmp)->value_arg[0], tmp);
	fork_process(p, hr_process(tmp, arena, idx, 1));
	return (*p);
}
