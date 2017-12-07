/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenoit <ybenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 19:57:34 by ybenoit           #+#    #+#             */
/*   Updated: 2017/10/02 11:51:08 by ybenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		ft_countmalloc_base(unsigned int c, size_t base)
{
	size_t	i;

	i = 0;
	while (c > 1)
	{
		c = c / base;
		i++;
	}
	return (i);
}

char				ft_converttochar(int c)
{
	if (c > 9)
		return ('a' + (c - 10));
	else
		return ('0' + c);
}

char				*ft_itoabase(unsigned int c, size_t base)
{
	int		i;
	char	*ret;
	char	*tmp;

	if (base > 16)
		return (NULL);
	i = 0;
	ret = (char*)malloc(sizeof(char) * (ft_countmalloc_base(c, base) + 1));
	while (c != 0)
	{
		ret[i++] = ft_converttochar(c % base);
		c = c / base;
	}
	ret[i] = '\0';
	tmp = ft_strrev(ret);
	free(ret);
	return (tmp);
}
