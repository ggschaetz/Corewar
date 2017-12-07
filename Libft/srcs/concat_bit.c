/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat_bit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 10:32:51 by ybenoit           #+#    #+#             */
/*   Updated: 2017/09/27 13:09:42 by arive-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*char_cat(char *str, char c)
{
	int len;

	len = ft_strlen(str);
	str[len] = c;
	str[len + 1] = '\0';
	return (str);
}

void	concat_bit(unsigned char c, char *str)
{
	unsigned char i;

	i = 1 << 7;
	while (i)
	{
		if (c & i)
			str = char_cat(str, '1');
		else
			str = char_cat(str, '0');
		i >>= 1;
	}
}
