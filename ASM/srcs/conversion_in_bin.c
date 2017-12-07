/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_in_bin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschaetz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 16:09:09 by gschaetz          #+#    #+#             */
/*   Updated: 2017/12/07 13:40:36 by gschaetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include <stdio.h>

void		recup_args(t_cmd *tmp)
{
	int n;
	int j;

	j = 0b00000011;
	n = 6;
	if (g_op_tab[tmp->hash_op].code != 1 && g_op_tab[tmp->hash_op].code != 9
	&& g_op_tab[tmp->hash_op].code != 12 && g_op_tab[tmp->hash_op].code != 15)
	{
		while (n > 0 && ft_strncmp(tmp->bin, "01", 2) != 0 && \
				ft_strncmp(tmp->bin, "09", 2) != 0 && \
				ft_strncmp(tmp->bin, "0c", 2) != 0)
		{
			if ((j & (tmp->ocp >> n)) == 1)
				recup_reg(tmp, (((n / 2) - 3) * -1));
			else if (((j & (tmp->ocp >> n)) == 2) || \
					((j & (tmp->ocp >> n)) == 3))
				recup_dir(tmp, (((n / 2) - 3) * -1));
			n -= 2;
			tmp->pos_arg_bin++;
		}
	}
	else
		fork_zjmp_live_in_bin(tmp, (((n / 2) - 3) * -1));
}

void		type_operation(t_cmd *tmp)
{
	if (g_op_tab[tmp->hash_op].code == 16)
	{
		tmp->bin[0] = '1';
		tmp->bin[1] = '0';
		tmp->bin[3] = '\0';
	}
	else
	{
		tmp->bin[0] = '0';
		tmp->bin[1] = '\0';
		tmp->bin = \
		ft_strjoin_free(tmp->bin, ft_itoabase(g_op_tab[tmp->hash_op].code, 16));
	}
}

void		conversion_in_bin(t_cmd **cmd, t_files file)
{
	t_cmd	*tmp;

	tmp = *cmd;
	tmp->pos_arg_bin = 0;
	while (tmp)
	{
		if (tmp->ocp != 0 || g_op_tab[tmp->hash_op].code == 1 || \
		g_op_tab[tmp->hash_op].code == 9 || g_op_tab[tmp->hash_op].code == 12
		||
		g_op_tab[tmp->hash_op].code == 15)
		{
			tmp->bin = ft_memalloc(tmp->size);
			tmp->arg_bin = ft_malloc_tab(3, 8);
			type_operation(tmp);
			if (ft_strcmp(tmp->bin, "09") != 0 && \
			ft_strcmp(tmp->bin, "0c") != 0 && g_op_tab[tmp->hash_op].code != 1
			&& g_op_tab[tmp->hash_op].code != 15)
				tmp->bin =
					ft_strjoin_free(tmp->bin, ft_itoabase(tmp->ocp, 16));
			recup_args(tmp);
			nb_to_character(tmp->bin, tmp->bin, tmp->size);
			write_in_output(file, tmp->bin, tmp->size);
		}
		tmp = tmp->next;
	}
}

void		conversion_in_bin_without_printing(t_cmd **cmd, t_files file)
{
	t_cmd	*tmp;

	tmp = *cmd;
	while (tmp)
	{
		if (tmp->ocp != 0 || g_op_tab[tmp->hash_op].code == 1 || \
		g_op_tab[tmp->hash_op].code == 9 || g_op_tab[tmp->hash_op].code == 12
		||
		g_op_tab[tmp->hash_op].code == 15)
		{
			tmp->bin = ft_memalloc(tmp->size);
			tmp->arg_bin = ft_malloc_tab(3, 8);
			type_operation(tmp);
			if (ft_strcmp(tmp->bin, "09") != 0 && \
			ft_strcmp(tmp->bin, "0c") != 0 && g_op_tab[tmp->hash_op].code != 1
			&&
			g_op_tab[tmp->hash_op].code != 15)
				tmp->bin = ft_strjoin_free(tmp->bin, ft_itoabase(tmp->ocp, 16));
			recup_args(tmp);
		}
		tmp = tmp->next;
	}
}
