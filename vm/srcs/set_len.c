/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschaetz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 11:13:46 by gschaetz          #+#    #+#             */
/*   Updated: 2017/11/30 11:39:33 by gschaetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int			set_len(int val_arg, int len, int dir)
{
	if (val_arg == 1)
		len += 1;
	else if (val_arg == 2)
		len += dir ? 2 : DIR_SIZE;
	else if (val_arg == 3)
		len += 2;
	return (len);
}
