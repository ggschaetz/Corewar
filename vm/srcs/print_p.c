/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkantzer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 09:48:11 by mkantzer          #+#    #+#             */
/*   Updated: 2017/11/30 18:00:35 by mkantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	three_params_verb(int val1, int val2, int val3, t_process **p)
{
	process_begin(p);
	if ((*p)->cur_op == 10)
		ft_printf(" r%i %i %i\n", val1, val2, val3);
	else if ((*p)->cur_op == 3 || (*p)->cur_op == 4)
		ft_printf(" r%i r%i r%i\n", val1, val2, val3);
	else
		ft_printf(" %i %i r%i\n", val1, val2, val3);
	if ((*p)->cur_op == 10 || (*p)->cur_op == 9 || (*p)->cur_op == 13)
		icmd_verb(val1, val2, val3, p);
}

void	icmd_verb(int val1, int val2, int val3, t_process **p)
{
	ft_printf("%8c -> ", '|');
	(*p)->cur_op == 10 ? ft_putstr("store to ") : ft_putstr("load from ");
	if ((*p)->cur_op == 9 || (*p)->cur_op == 13)
	{
		ft_printf("%i + %i = %i", val1, val2, val1 + val2);
		ft_putstr(" (with pc");
		if ((*p)->cur_op == 9)
			ft_printf(" and mod %i)\n", ((*p)->pc->prev_pc +\
					(*p)->champ->vm_pos + (val1 + val2) % IDX_MOD));
		else
			ft_printf(" %i)\n", val1 + val2 + (*p)->pc->prev_pc);
	}
	else
	{
		ft_printf("%i + %i = %i", val2, val3, val2 + val3);
		ft_printf(" (with pc and mod %i)\n", ((*p)->pc->prev_pc +\
					(*p)->champ->vm_pos + ((val2 + val3) % IDX_MOD)));
	}
}

void	process_begin(t_process **p)
{
	ft_putchar('P');
	if ((*p)->pid < 10)
		ft_putstr("    ");
	else if ((*p)->pid >= 100)
		ft_putstr("  ");
	else
		ft_putstr("   ");
	ft_printf("%i | %s", (*p)->pid, g_op_tab[(*p)->cur_op].name);
}

void	two_params_verb(int val1, int val2, t_process **p)
{
	process_begin(p);
	if ((*p)->cur_op == 1 || (*p)->cur_op == 12)
		ft_printf(" %i r%i\n", val1, val2);
	else
		ft_printf(" r%i %i\n", val1, val2);
}

void	one_param_verb(int val1, t_process **p)
{
	process_begin(p);
	ft_printf(" %i", val1);
	if ((*p)->cur_op == 11)
		ft_printf(" (%i)", (*p)->pc->prev_pc + (*p)->champ->vm_pos +\
				val1 % IDX_MOD);
	else if ((*p)->cur_op == 14)
		ft_printf(" (%i)", (*p)->pc->prev_pc + (*p)->champ->vm_pos + val1);
	if ((*p)->cur_op == 8)
		(*p)->carry == 1 ? ft_putstr(" OK") : ft_putstr(" FAILED");
	ft_putchar('\n');
}
