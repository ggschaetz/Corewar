/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkantzer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 17:44:50 by mkantzer          #+#    #+#             */
/*   Updated: 2017/12/05 13:29:51 by mkantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	init_vm(t_arena **arena, t_champ **champ, t_process **p)
{
	t_champ	*tmp;
	int		i;

	tmp = *champ;
	i = 0;
	(*arena)->sum_lives = 0;
	(*arena)->cur_cycle = 0;
	(*arena)->nb_p = 1;
	(*arena)->die_cycle = CYCLE_TO_DIE;
	(*arena)->winner = 0;
	ft_bzero((*arena)->arena, MEM_SIZE);
	if ((*arena)->nb_player > 1)
		while (i++ < (*arena)->nb_player - 1)
			tmp = tmp->next;
	i = 0;
	while (i < (*arena)->nb_player)
	{
		tmp->vm_pos = i * (MEM_SIZE / (*arena)->nb_player);
		ft_memcpy((*arena)->arena + tmp->vm_pos, tmp->champ,\
				tmp->head->prog_size);
		add_process(p, cr_process(&tmp, (*arena)->nb_p));
		tmp = tmp->previous;
		(*arena)->nb_p++;
		i++;
	}
}

void	init_champ(t_champ **champ)
{
	(*champ)->pos = 0;
	(*champ)->vm_pos = 0;
	(*champ)->head = ft_memalloc(sizeof(t_header));
	(*champ)->head->magic = 0;
	(*champ)->head->prog_size = 0;
}

void	init_v(t_verb **v, int nb)
{
	(*v)->base = 1;
	if ((0b00000001 & nb) == 1 && nb <= 31 && nb > 0)
		(*v)->lives = 1;
	if ((0b00000010 & nb) == 2 && nb <= 31 && nb > 0)
		(*v)->cycles = 1;
	if ((0b00000100 & nb) == 4 && nb <= 31 && nb > 0)
		(*v)->op = 1;
	if ((0b00001000 & nb) == 8 && nb <= 31 && nb > 0)
		(*v)->deaths = 1;
	if ((0b00010000 & nb) == 16 && nb <= 31 && nb > 0)
		(*v)->pc = 1;
}

void	free_all(t_arena **arena, t_process **p, t_champ **champ, t_verb **v)
{
	t_process	*tmp;

	free(*v);
	free(*arena);
	free((*champ)->head);
	free(*champ);
	while (*p)
	{
		tmp = *p;
		free(tmp->pc);
		free(tmp);
		(*p) = (*p)->next;
	}
}
