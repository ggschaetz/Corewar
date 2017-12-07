/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arive-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:10:29 by arive-de          #+#    #+#             */
/*   Updated: 2017/11/29 18:21:24 by arive-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		live(t_process **p, t_arena **arena, t_verb **v)
{
	int			i;
	t_process	*tmp;

	i = 0;
	tmp = *p;
	(*p)->nb_live++;
	(*p)->l_live = (*arena)->cur_cycle;
	arg_value(p, arena, 0);
	if ((*v)->op)
		one_param_verb((*p)->value_arg[0], p);
	while (i < (*arena)->nb_player && tmp)
	{
		if ((*p)->value_arg[0] == tmp->champ->pos)
		{
			tmp->champ->nb_lives++;
			(*arena)->winner = (*p)->champ->pos;
			(*p)->champ->l_live = (*arena)->cur_cycle;
			if ((*v)->lives && (*p)->champ->pos == tmp->champ->pos)
				print_verb(p, arena, 1);
		}
		(*arena)->sum_lives++;
		i++;
		tmp = tmp->next;
	}
	return (0);
}
