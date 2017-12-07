/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arive-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:05:50 by arive-de          #+#    #+#             */
/*   Updated: 2017/11/30 19:27:02 by mkantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		add(t_process **p, t_arena **arena, t_verb **v)
{
	int val1;
	int val2;
	int val3;

	arg_value(p, arena, 3);
	val1 = (*p)->value_arg[0];
	val2 = (*p)->value_arg[1];
	val3 = (*p)->value_arg[2];
	(*p)->r[val3 - 1] = (*p)->r[val1 - 1] + (*p)->r[val2 - 1];
	(*p)->carry = (*p)->r[val3 - 1] == 0 ? 1 : 0;
	if ((*v)->op)
		three_params_verb(val1, val2, val3, p);
	return (0);
}
