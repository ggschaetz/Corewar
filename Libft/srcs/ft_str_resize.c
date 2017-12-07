/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arive-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 16:28:04 by arive-de          #+#    #+#             */
/*   Updated: 2017/11/30 16:28:07 by arive-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_resize(char *str, int start, int end)
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
	free(str);
	str = ret;
	return (str);
}
