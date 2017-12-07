/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkeur.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschaetz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 15:37:21 by gschaetz          #+#    #+#             */
/*   Updated: 2017/11/30 19:19:54 by mkantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		ft_check_reg(t_process **tmp, int pos_arg, int *arg, t_arena **arena)
{
	int		pos;
	int		i;

	pos = 2;
	i = 0;
	while (i < pos_arg)
	{
		if (arg[i] == 2)
			pos += g_op_tab[(*tmp)->cur_op].ix ? 2 : DIR_SIZE;
		else if (arg[i] == 1)
			pos += 1;
		else
			pos += 2;
		i++;
	}
	if ((*arena)->arena[((*tmp)->ocp + pos - 1) % MEM_SIZE] > REG_NUMBER || \
			(*arena)->arena[((*tmp)->ocp + pos - 1) % MEM_SIZE] < 1)
		return (0);
	return (1);
}

int		ft_check_ocp(t_process **tmp, int pos_arg, int *arg)
{
	int i;
	int	size;

	i = 0;
	while (i <= pos_arg)
	{
		size = g_op_tab[(*tmp)->cur_op].size[i];
		if (arg[i] == 2)
		{
			if (size == 1 || size == 4 || size == 5)
				return (0);
		}
		else if (arg[i] == 1)
		{
			if (size == 2 || size == 4)
				return (0);
		}
		else
		{
			if (size < 4 && arg[i] != 0)
				return (0);
		}
		i++;
	}
	return (1);
}

int		ret_read(t_process *tmp, t_arena **arena, int len, t_verb **v)
{
	tmp->pc->nb_octet = len;
	tmp->pc->cur_pc = tmp->pc->prev_pc + len;
	if ((*v)->pc)
		print_verb(&tmp, arena, 5);
	tmp->pc->prev_pc = tmp->pc->cur_pc;
	tmp->checkeur = 1;
	return (0);
}

int		checkeur_args(t_process **tmp, t_arena **arena, t_verb **v, int *arg)
{
	int i;
	int	len;
	int nb_null;
	int	nb_fail_reg;
	int	ocp_f;

	i = -1;
	len = 2;
	nb_null = 0;
	nb_fail_reg = 0;
	ocp_f = 0;
	while (++i < g_op_tab[(*tmp)->cur_op].param)
	{
		if (!(ft_check_ocp(tmp, i, arg)))
			ocp_f++;
		if (arg[i] == 0)
			nb_null += 1;
		else if (arg[i] == 1 && ft_check_reg(tmp, i, arg, arena) == 0 && ++len)
			nb_fail_reg++;
		else
			len = set_len(arg[i], len, g_op_tab[(*tmp)->cur_op].ix);
	}
	if (nb_null != 0 || nb_fail_reg != 0 || ocp_f != 0)
		return (ret_read((*tmp), arena, len, v));
	return (1);
}

int		checkeur(t_process **tmp, t_arena **arena, t_verb **v)
{
	int			arg[3];
	int			i;
	int			j;

	i = 0;
	j = 6;
	if ((*tmp)->cur_op > 15 || (*tmp)->cur_op < 0)
	{
		(*tmp)->pc->prev_pc++;
		(*tmp)->pc->cur_pc = (*tmp)->pc->prev_pc;
		return (0);
	}
	if ((*tmp)->cur_op != 0 && (*tmp)->cur_op != 14 && (*tmp)->cur_op != 11 \
			&& (*tmp)->cur_op != 8 && (*tmp)->cur_op != 15)
	{
		while (i < g_op_tab[(*tmp)->cur_op].param)
		{
			arg[i] = ((*arena)->arena[((*tmp)->ocp) % MEM_SIZE] >> j) & 3;
			i++;
			j -= 2;
		}
		if (checkeur_args(tmp, arena, v, arg) != 1)
			return (0);
	}
	return (1);
}
