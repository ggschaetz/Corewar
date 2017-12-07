/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arive-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:09:36 by arive-de          #+#    #+#             */
/*   Updated: 2017/11/30 21:18:20 by mkantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

t_process	*init_process(t_process **p, t_process *new, t_arena **arena)
{
	int i;

	i = -1;
	while (++i <= 15)
		new->r[i] = (*p)->r[i];
	new->pc->prev_pc = (*p)->pc->prev_pc;
	new->pc->nb_octet = 3;
	new->pid = (*arena)->nb_p++;
	new->ocp = 0;
	new->cur_op = 11;
	new->l_live = (*arena)->cur_cycle;
	new->nb_live = 0;
	new->cycle_to_go = -2;
	new->champ = (*p)->champ;
	new->carry = (*p)->carry;
	return (new);
}

t_process	*hr_process(t_process **p, t_arena **arena, int idx, int lfork)
{
	t_process *new;

	if (!(new = (t_process *)ft_memalloc(sizeof(t_process))))
		return (NULL);
	new->pc = (t_pc *)ft_memalloc(sizeof(t_pc));
	if (!lfork)
	{
		if ((*p)->pc->prev_pc + idx % IDX_MOD < 0)
			new->pc->cur_pc = (MEM_SIZE + (((*p)->pc->prev_pc -
											(ABS(idx) % IDX_MOD))) % MEM_SIZE);
		else
			new->pc->cur_pc = ((*p)->pc->prev_pc + idx % IDX_MOD) % MEM_SIZE;
	}
	else
	{
		if ((*p)->pc->prev_pc + idx < 0)
			new->pc->cur_pc = (MEM_SIZE + ((*p)->pc->prev_pc -
														(ABS(idx)))) % MEM_SIZE;
		else
			new->pc->cur_pc = ((*p)->pc->prev_pc + idx) % MEM_SIZE;
	}
	new = init_process(p, new, arena);
	return (new);
}

void		fork_process(t_process **p, t_process *new)
{
	if (!p || !new)
		return ;
	(*p)->previous = new;
	new->next = *p;
	new->previous = 0;
	*p = new;
}

t_process	*op_spe(t_process **p, t_process **tmp, t_arena **arena, t_verb **v)
{
	int idx;

	arg_value(tmp, arena, 11);
	idx = (*tmp)->value_arg[0];
	if ((*v)->op)
		one_param_verb((*tmp)->value_arg[0], tmp);
	fork_process(p, hr_process(tmp, arena, idx, 0));
	return (*p);
}
