/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_f.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arive-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 11:05:13 by mkantzer          #+#    #+#             */
/*   Updated: 2017/11/30 18:34:38 by mkantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		m0d(int value, int mod)
{
	int	sign;
	int res;

	sign = value < 0 ? -1 : 1;
	res = (value < 0 ? -value : value) % mod;
	return (sign * res);
}

void	put_value_arena(t_process **p, t_arena **arena, int val1, int val2)
{
	int32_t	nb;
	int		i;
	char	*str;

	i = 3;
	str = ft_itoa_base((*p)->r[val1 - 1], 2);
	nb = ft_atoi_base(str, 2);
	ft_strdel(&str);
	nb = (*p)->r[val1 - 1] < 0 ? (~nb + 1) : nb;
	while (val2 < 0)
		val2 += MEM_SIZE;
	val2 %= MEM_SIZE;
	while (i >= 0)
	{
		(*arena)->arena[(val2 + i) % MEM_SIZE] = nb;
		nb = nb >> 8;
		i--;
	}
}

int		get_value_arena(t_arena **arena, int val1, int idx)
{
	int		nb;
	int		i;
	char	*str;

	i = 4;
	str = ft_strnew(32);
	while (val1 < 0)
		val1 += MEM_SIZE;
	val1 %= MEM_SIZE;
	idx = 0;
	while (i > 0)
	{
		concat_bit((*arena)->arena[val1 % MEM_SIZE], str);
		val1++;
		i--;
	}
	nb = (*str == '0' ? ft_atoi_base(str, 2) : n_dec(str));
	ft_strdel(&str);
	return (nb);
}
