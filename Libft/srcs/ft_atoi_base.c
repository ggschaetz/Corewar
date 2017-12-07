/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arive-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 16:22:05 by arive-de          #+#    #+#             */
/*   Updated: 2017/11/30 16:23:33 by arive-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int		change_char(char str, int base)
{
	if (ft_isdigit(str))
		return (str - '0');
	else if (str >= 'A' && str <= 'F')
		return (str - 55);
	else if (str >= 'a' && str <= 'f')
		return (str - 87);
	else
		return (0);
}

static long		give_base(char *str, int base)
{
	long	value;
	double	power;
	int		i;

	value = 0;
	i = 0;
	while (ft_isspace(*str))
		str++;
	if (*str && (*str == '0' && ((*str + 1 == 'x' || *str + 1 == 'X') ||
					(*str + 1 == 'b' || *str + 1 == 'B'))))
	{
		str++;
		str++;
	}
	while (str[i])
		i++;
	power = i - 1;
	while (*str)
	{
		value = value + (ft_pow((double)base, power) *
				(change_char(*str, base)));
		power--;
		str++;
	}
	return (value);
}

long			ft_atoi_base(char *str, int base)
{
	if (base != 10 && base != 16 && base != 8 && base != 2)
		return (0);
	else if (base == 16)
		return (give_base(str, 16));
	else if (base == 10)
		return (give_base(str, 10));
	else if (base == 8)
		return (give_base(str, 8));
	else if (base == 2)
		return (give_base(str, 2));
	else
		return (0);
}
