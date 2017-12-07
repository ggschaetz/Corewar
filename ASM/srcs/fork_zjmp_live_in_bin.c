/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_zjmp_live_in_bin.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschaetz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 11:18:29 by gschaetz          #+#    #+#             */
/*   Updated: 2017/10/25 15:48:15 by gschaetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	live(t_cmd *tmp, int postion_arg)
{
	if (ft_strncmp(tmp->args[0], "%", 1) == 0)
		live_entier(tmp, postion_arg);
	else
		live_label(tmp, postion_arg);
}

void	zjmp(t_cmd *tmp, int postion_arg)
{
	int		nb;

	if (tmp->label_values[postion_arg] < 0)
	{
		nb = 0xffff + tmp->label_values[postion_arg] + 1;
		tmp->arg_bin[tmp->pos_arg_bin] = \
		ft_strjoin_free(tmp->arg_bin[tmp->pos_arg_bin], ft_itoabase(nb, 16));
		tmp->bin = ft_strjoin_free(tmp->bin, ft_itoabase(nb, 16));
	}
	else if (tmp->label_values[postion_arg] > 0)
		adressage_positif_label(tmp, postion_arg);
	else
		zjmp_indirect(tmp, postion_arg);
}

void	fork_zjmp_live_in_bin(t_cmd *tmp, int postion_arg)
{
	if (g_op_tab[tmp->hash_op].code == 1)
		live(tmp, postion_arg);
	if (g_op_tab[tmp->hash_op].code == 9 || g_op_tab[tmp->hash_op].code == 12
			||
			g_op_tab[tmp->hash_op].code == 15)
		zjmp(tmp, postion_arg);
	tmp->pos_arg_bin++;
}
