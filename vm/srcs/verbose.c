/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkantzer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 19:46:55 by mkantzer          #+#    #+#             */
/*   Updated: 2017/12/05 13:35:24 by mkantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	print_player(t_champ *tmp, int i)
{
	if (tmp == NULL)
		return ;
	print_player(tmp->next, --i);
	ft_printf("* Player %i, weighing %i bytes, \"%s\" (\"%s\") !\n", tmp->pos *\
			-1, tmp->head->prog_size, tmp->head->prog_name,\
			tmp->head->comment);
}

void	print_pc(t_process **p, t_arena **arena)
{
	int i;
	int nb;

	i = (*p)->pc->nb_octet;
	nb = (*p)->pc->prev_pc;
	ft_printf("ADV %i (%.4p -> %.4p) ", i, ((*p)->pc->prev_pc +\
			(*p)->champ->vm_pos) % MEM_SIZE, ((*p)->pc->cur_pc +\
				(*p)->champ->vm_pos) % MEM_SIZE);
	while (i)
	{
		if ((*arena)->arena[(nb + (*p)->champ->vm_pos) % MEM_SIZE] == 0)
			ft_putstr("00 ");
		else
			ft_printf("%.2hhx ", (*arena)->arena[(nb +\
						(*p)->champ->vm_pos) % MEM_SIZE]);
		nb++;
		i--;
	}
	ft_putchar('\n');
}

void	print_verb(t_process **p, t_arena **arena, int code)
{
	if (code == 1)
		ft_printf("Player %i (%s) is said to be alive\n",\
				(*p)->champ->pos * -1, (*p)->champ->head->prog_name);
	if (code == 2)
		ft_printf("Cycle to die is now %i\n", (*arena)->die_cycle);
	if (code == 3 && (*arena)->cur_cycle != 0)
		ft_printf("It is now cycle %i\n", (*arena)->cur_cycle);
	if (code == 4)
	{
		ft_printf("Process %i hasn't lived for %i cycles (CTD %i)\n",\
				(*p)->pid, ((*arena)->cur_cycle - (*p)->l_live) - 1,\
				(*arena)->die_cycle);
	}
	if (code == 5 && ((*p)->cur_op != 8 || (*p)->carry == 0))
		print_pc(p, arena);
}
