/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cur_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkantzer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 18:12:47 by mkantzer          #+#    #+#             */
/*   Updated: 2017/11/30 18:31:31 by mkantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		invalid_cur_op(t_process **p, int tab_op, int pos)
{
	if ((*p)->pc->prev_pc != (*p)->pc->cur_pc - 1 && ((*p)->cur_op == 11 ||\
				(*p)->cur_op == 14))
		(*p)->pc->cur_pc++;
	(*p)->pc->prev_pc = (*p)->pc->cur_pc;
	(*p)->pc->cur_pc++;
	if ((*p)->pc->cur_pc > 4095)
	{
		(*p)->pc->cur_pc = (*p)->pc->cur_pc % MEM_SIZE;
		(*p)->cycle_to_go += 1;
	}
	(*p)->ocp = pos + 1;
	(*p)->cur_op = tab_op;
	return (-3);
}

int		cur_op(t_arena **arena, t_process **p)
{
	int po;
	int i;
	int tab_op;

	po = (*p)->pc->cur_pc + (*p)->champ->vm_pos;
	tab_op = (*arena)->arena[po % MEM_SIZE] - 1;
	i = g_op_tab[tab_op].ix;
	if (tab_op < 0 || (*arena)->arena[po % MEM_SIZE] > 15)
		return (invalid_cur_op(p, tab_op, po));
	(*p)->pc->prev_pc = (*p)->pc->cur_pc;
	if (g_op_tab[tab_op].param != 1)
		(*p)->pc->cur_pc += pc_args(p, (*arena)->arena[(po % MEM_SIZE) + 1], i);
	else if (i)
	{
		(*p)->pc->cur_pc += 3;
		(*p)->pc->nb_octet = 3;
	}
	else
	{
		(*p)->pc->cur_pc += DIR_SIZE + 1;
		(*p)->pc->nb_octet = DIR_SIZE + 1;
	}
	(*p)->ocp = po + 1;
	(*p)->cur_op = tab_op;
	return (tab_op);
}

int		pc_args(t_process **p, unsigned char c, int ix)
{
	int nb;
	int n;
	int j;
	int i;

	nb = 2;
	j = 0b00000011;
	i = 0;
	n = 6;
	while (n > 0)
	{
		if ((j & (c >> n)) == 1)
			nb++;
		else if ((j & (c >> n)) == 2)
			nb += (ix) ? 2 : DIR_SIZE;
		else if ((j & (c >> n)) == 3)
			nb += IND_SIZE;
		((j & (c >> n)) == 2 && ix) ? (*p)->dir++ : 0;
		((j & (c >> n)) == 3) ? (*p)->ind++ : 0;
		(*p)->size_arg[i++] = nb - 2;
		n -= 2;
	}
	if (g_op_tab[(*p)->cur_op].op_code != 9)
		(*p)->pc->nb_octet = nb;
	return (nb);
}
