/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkantzer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 22:14:06 by mkantzer          #+#    #+#             */
/*   Updated: 2017/11/30 22:15:51 by mkantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void		rip_split(t_process **p)
{
	if ((*p)->next == NULL)
	{
		((*p)->previous)->next = NULL;
		free((*p)->pc);
		free((*p));
	}
	else if ((*p)->next && (*p)->previous)
	{
		((*p)->previous)->next = (*p)->next;
		((*p)->next)->previous = (*p)->previous;
		free((*p)->pc);
		free((*p));
	}
}

int			rip_process(t_process **p, t_arena **arena, t_verb **v)
{
	t_process	*tmp;

	if ((*v)->deaths)
		print_verb(p, arena, 4);
	if (*arena && *v && (*p)->next == NULL && (*p)->previous == NULL)
	{
		*p = NULL;
		return (0);
	}
	else if ((*p)->previous == NULL)
	{
		tmp = *p;
		free(tmp->pc);
		free(tmp);
		((*p)->next)->previous = NULL;
		*p = (*p)->next;
		return (1);
	}
	else
		rip_split(p);
	while ((*p)->previous)
		(*p) = (*p)->previous;
	return (1);
}
