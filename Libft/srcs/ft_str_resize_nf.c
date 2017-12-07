/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_resize_nf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arive-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 16:29:44 by arive-de          #+#    #+#             */
/*   Updated: 2017/11/30 16:29:46 by arive-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_resize_nf(char *str, int start, int end)
{
	char	*ret;
	int		i;

	if (end > (int)ft_strlen(str))
		return (str);
	i = 0;
	ret = (char*)malloc(sizeof(char) * (end - start + 1));
	while (start < end)
		ret[i++] = str[start++];
	ret[i] = '\0';
	return (ret);
}
