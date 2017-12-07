/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkantzer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 17:16:18 by mkantzer          #+#    #+#             */
/*   Updated: 2017/11/30 19:13:13 by mkantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		play(t_arena **arena, t_process **p, t_verb **v)
{
	int			win;
	int			i;
	int			max;

	i = 1;
	win = 0;
	max = 1;
	while (win != 1)
	{
		if ((i + (*arena)->die_cycle) == (*arena)->cur_cycle)
		{
			if ((max = ctd_handler(arena, p, v, max)) == -1)
				win = 1;
			i = (*arena)->cur_cycle;
		}
		if (((*arena)->die_cycle <= 0 || (*p) == NULL) && !win)
			win = 1;
		if ((*v)->cycles && !win)
			print_verb(p, arena, 3);
		if ((*arena)->dump == (*arena)->cur_cycle && !win)
			return (dump_vm(arena));
		!win ? process_play(arena, p, v) : 0;
		(*arena)->cur_cycle++;
	}
	return (1);
}

int		ctd_handler(t_arena **arena, t_process **p, t_verb **v, int max)
{
	if ((check_process(p, arena, v)) == 0)
		return (-1);
	if ((*arena)->sum_lives >= NBR_LIVE || max == MAX_CHECKS)
	{
		max = 0;
		(*arena)->sum_lives = 0;
		(*arena)->die_cycle -= CYCLE_DELTA;
		if ((*v)->cycles)
			print_verb(p, arena, 2);
	}
	else
		(*arena)->sum_lives = 0;
	max++;
	return (max);
}

int		check_process(t_process **p, t_arena **arena, t_verb **v)
{
	t_process *tmp;

	tmp = *p;
	while (tmp)
	{
		if (tmp->l_live < ((*arena)->cur_cycle - (*arena)->die_cycle))
		{
			if (!(rip_process(&tmp, arena, v)))
				return (0);
			*p = tmp;
		}
		else
			tmp = tmp->next;
	}
	return (1);
}

void	cycle_to_go_zero(t_process *tmp, t_arena **arena)
{
	if (tmp->cur_op == 11 || tmp->cur_op == 14)
		tmp->pc->prev_pc = tmp->pc->cur_pc;
	if (!(tmp->checkeur))
	{
		cur_op(arena, &tmp);
		if (tmp->cycle_to_go == -2 && tmp->cur_op >= 0 && tmp->cur_op <= 15)
			tmp->cycle_to_go = g_op_tab[tmp->cur_op].cycles - 1;
		else if (tmp->cycle_to_go < 0 && tmp->cur_op >= 0 && tmp->cur_op <= 15)
			tmp->cycle_to_go = g_op_tab[tmp->cur_op].cycles;
	}
	else
	{
		tmp->checkeur = 0;
		tmp->cycle_less = 1;
	}
	if (tmp->cycle_less)
	{
		if ((*arena)->arena[tmp->pc->cur_pc] > 0 &&\
				(*arena)->arena[tmp->pc->cur_pc] < 17)
		{
			cur_op(arena, &tmp);
			tmp->cycle_to_go = g_op_tab[tmp->cur_op].cycles;
			tmp->cycle_less = 0;
		}
	}
}

int		process_play(t_arena **arena, t_process **p, t_verb **v)
{
	t_process	*tmp;

	tmp = *p;
	while (tmp)
	{
		if (tmp->cycle_to_go == 0 && checkeur(&tmp, arena, v) != 0)
		{
			if (tmp->cur_op == 11)
				*p = op_spe(p, &tmp, arena, v);
			else if (tmp->cur_op == 14)
				*p = op_lspe(p, &tmp, arena, v);
			else
				g_op_tab[tmp->cur_op].f(&tmp, arena, v);
			tmp->cycle_to_go--;
			if ((*v)->pc)
				print_verb(&tmp, arena, 5);
		}
		if (tmp->cycle_to_go <= 0)
			cycle_to_go_zero(tmp, arena);
		tmp->cycle_to_go--;
		tmp = tmp->next;
	}
	return (1);
}
