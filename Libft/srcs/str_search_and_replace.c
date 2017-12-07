/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_search_and_replace.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arive-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 16:30:07 by arive-de          #+#    #+#             */
/*   Updated: 2017/11/30 16:30:09 by arive-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void		str_search_and_replace(char *str, char *pattern, char *replace)
{
	char *find;

	find = ft_strstr(str, pattern);
	if (find && ft_strlen(pattern) == ft_strlen(replace))
	{
		while (*replace)
		{
			*find = *replace;
			find++;
			replace++;
		}
	}
}
