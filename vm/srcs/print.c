/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkantzer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 19:46:55 by mkantzer          #+#    #+#             */
/*   Updated: 2017/11/30 19:19:30 by mkantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	print_state(t_arena **arena)
{
	ft_printf("\nCYCLE nº%i\n", (*arena)->cur_cycle);
	ft_printf(" Total lives : %i\n", (*arena)->sum_lives);
}

void	print_champ(t_champ *champ)
{
	t_champ	*tmp;
	int		i;

	tmp = champ;
	while (tmp)
	{
		i = 0;
		print_header(*tmp->head);
		ft_printf(" curr = %p\n", tmp);
		ft_printf(" next = %p\n", tmp->next);
		ft_printf(" prev = %p\n", tmp->previous);
		ft_printf(" pos = %i\n", tmp->pos);
		ft_printf(" vm_pos = %i\n", tmp->vm_pos);
		ft_putstr(" champ =");
		while (i < CHAMP_MAX_SIZE)
		{
			ft_putchar(' ');
			ft_printf("%x", tmp->champ[i]);
			i++;
		}
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

void	print_header(t_header head)
{
	ft_printf("Name = %s\n", head.prog_name);
	ft_printf(" magic = %x\n", head.magic);
	ft_printf(" prog_size = %i\n", head.prog_size);
	ft_printf(" comment = %s\n", head.comment);
}

void	print_s_verb(t_verb **v)
{
	ft_printf("Verbose\n");
	ft_printf(" pc     : %i\n", (*v)->pc);
	ft_printf(" op     : %i\n", (*v)->op);
	ft_printf(" base   : %i\n", (*v)->base);
	ft_printf(" lives  : %i\n", (*v)->lives);
	ft_printf(" cycles : %i\n", (*v)->cycles);
	ft_printf(" deaths : %i\n", (*v)->deaths);
}

void	print_p(t_process **p)
{
	t_process	*tmp;
	int			i;

	tmp = *p;
	while (tmp)
	{
		i = 0;
		ft_printf("PROCESS %i\n", tmp->pid);
		ft_printf(" Champ : ad: %p pos: %i\n", tmp->champ, tmp->champ->pos);
		ft_printf(" Live  : last: %i nb: %i\n", tmp->l_live, tmp->nb_live);
		ft_printf(" Cycle : %i\n", tmp->cycle_to_go);
		ft_printf(" Op   : %i = %s\n", tmp->cur_op, g_op_tab[tmp->cur_op].name);
		ft_printf(" Ocp   : %i\n", tmp->ocp);
		ft_printf(" Carry : %i\n", tmp->carry);
		ft_printf(" PC    :\n");
		ft_printf("  cur  : %i\n", tmp->pc->cur_pc);
		ft_printf("  prev : %i\n", tmp->pc->prev_pc);
		ft_printf("  nb   : %i\n", tmp->pc->nb_octet);
		ft_printf(" Registres :\n");
		ft_printf("  r[0] : %i\n", tmp->r[0]);
		tmp = tmp->next;
	}
}
