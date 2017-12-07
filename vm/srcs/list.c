/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkantzer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 17:07:58 by mkantzer          #+#    #+#             */
/*   Updated: 2017/12/04 15:10:48 by arive-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

t_champ		*cr_champ(void)
{
	t_champ	*new;

	new = (t_champ*)malloc(sizeof(t_champ));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

void		add_champ(t_champ **champ, t_champ *new)
{
	t_champ *tmp;

	if (!champ || !new)
		return ;
	if (!(*champ))
	{
		new->previous = 0;
		*champ = new;
	}
	else
	{
		(*champ)->previous = new;
		tmp = *champ;
		*champ = new;
		new->next = tmp;
	}
}

t_process	*cr_process(t_champ **champ, int pid)
{
	t_process	*new;

	new = (t_process *)ft_memalloc(sizeof(t_process));
	if (!new)
		return (NULL);
	new->pc = (t_pc *)ft_memalloc(sizeof(t_pc));
	new->pc->cur_pc = 0;
	new->pid = pid;
	new->ocp = 0;
	new->cur_op = -1;
	new->l_live = 0;
	new->nb_live = 0;
	new->checkeur = 0;
	new->cycle_less = 0;
	new->cycle_to_go = -1;
	new->champ = *champ;
	new->carry = 0;
	new->next = NULL;
	new->r[0] = (*champ)->pos;
	return (new);
}

void		add_process(t_process **p, t_process *new)
{
	t_process *tmp;

	if (!p || !new)
		return ;
	if (!(*p))
	{
		new->previous = 0;
		*p = new;
	}
	else
	{
		(*p)->previous = new;
		tmp = *p;
		*p = new;
		new->next = tmp;
	}
}

void		free_champ(t_champ **champ, t_arena **arena)
{
	t_champ *tmp;

	while (*champ)
	{
		tmp = *champ;
		free(tmp->head);
		free(tmp);
		*champ = (*champ)->next;
	}
	free(*champ);
	free(*arena);
}
