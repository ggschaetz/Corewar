/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arive-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 15:16:02 by arive-de          #+#    #+#             */
/*   Updated: 2017/11/30 17:15:48 by ybenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uintmax_t	ft_size(uintmax_t n, int base)
{
	unsigned long long size;

	size = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / base;
		size++;
	}
	return (size);
}

char		*ft_conv(uintmax_t nb, int base, int size, int i)
{
	char	*tab;
	char	*str;

	str = ft_strnew(size + i);
	tab = ft_strdup("0123456789abcdef");
	size = size - 1;
	while (size >= i)
	{
		str[size] = tab[nb % base];
		nb = nb / base;
		size--;
	}
	ft_strdel(&tab);
	return (str);
}

char		*ft_itoa_base(intmax_t value, int base)
{
	int					i;
	char				*str;
	long long			size;
	uintmax_t			uvalue;

	i = 0;
	if (base <= 1 || base >= 17)
		return (NULL);
	uvalue = (value < 0 ? value * -1 : value);
	size = ft_size(uvalue, base);
	if (base == 10)
		i = (value < 0 ? 1 : 0);
	str = ft_conv(uvalue, base, size + i, i);
	if (i == 1)
		str[0] = '-';
	return (str);
}
