/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arive-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 11:02:01 by arive-de          #+#    #+#             */
/*   Updated: 2017/11/30 17:00:59 by ybenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		n_dec(char *str)
{
	int i;
	int nb;

	i = 0;
	while (str[i])
	{
		str[i] = (str[i] == '1' ? '0' : '1');
		i++;
	}
	nb = ft_atoi_base(str, 2) + 1;
	return (-nb);
}

void	convert_value(t_process **p, t_arena **arena, int *size, int nb_args)
{
	char	*str;
	int		i;
	int		res;

	res = 0;
	i = 0;
	if (nb_args > 1)
		(*p)->ocp += 1;
	while (i < nb_args)
	{
		str = ft_strnew(32);
		while (size[i] > 0)
		{
			concat_bit((*arena)->arena[(*p)->ocp % MEM_SIZE], str);
			(*p)->ocp += 1;
			size[i]--;
		}
		(*p)->value_arg[i] = (*str == '1' ? n_dec(str) : ft_atoi_base(str, 2));
		ft_strdel(&str);
		i++;
	}
}

void	size_value(t_process **p, t_arena **arena, int nb_args, int ix)
{
	int		i;
	int		size[3];

	i = 0;
	(*p)->prev_ocp = (*p)->ocp - 1;
	pc_args(p, (*arena)->arena[(*p)->ocp % MEM_SIZE], ix);
	while (i < nb_args)
	{
		if (i == 1)
			(*p)->size_arg[i] = (*p)->size_arg[i] - (*p)->size_arg[i - 1];
		else if (i == 2)
			(*p)->size_arg[i] = (*p)->size_arg[i] - (*p)->size_arg[i - 1]
													- (*p)->size_arg[i - 2];
		if (!((size[i]) = (*p)->size_arg[i]))
		{
			size[i] = 2;
			(*p)->ind++;
		}
		i++;
	}
	convert_value(p, arena, size, nb_args);
}

void	arg_value(t_process **p, t_arena **arena, int tab_op)
{
	int ix;
	int nb_args;
	int size[3];

	ix = g_op_tab[tab_op].ix;
	nb_args = g_op_tab[tab_op].param;
	(*p)->dir = 0;
	(*p)->ind = 0;
	if (tab_op == 0 || tab_op == 11 || tab_op == 14)
	{
		size[0] = tab_op == 0 ? 4 : 2;
		convert_value(p, arena, size, 1);
	}
	else
	{
		size_value(p, arena, nb_args, ix);
	}
}
