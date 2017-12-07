/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arive-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 16:24:12 by arive-de          #+#    #+#             */
/*   Updated: 2017/11/30 16:27:47 by arive-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char		*cut_str(char *str, int cut)
{
	int		len;

	if (((len = ft_strlen(str)) - cut) < 0)
		return (str);
	str[ft_strlen(str) - cut] = '\0';
	return (str);
}
