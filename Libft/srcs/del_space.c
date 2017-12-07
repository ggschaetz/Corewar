/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arive-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 16:24:43 by arive-de          #+#    #+#             */
/*   Updated: 2017/11/30 16:24:45 by arive-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void		del_space(char **str)
{
	int		i;
	int		j;
	int		k;
	char	tmp[64];

	i = 0;
	j = 0;
	if (!str)
		return ;
	while (str[i])
	{
		k = 0;
		j = 0;
		while (str[i][j] && str[i][j] == ' ')
			j++;
		while (str[i][j] && str[i][j] != ' ')
		{
			tmp[k] = str[i][j];
			j++;
			k++;
		}
		tmp[k] = '\0';
		str[i] = ft_strcpy(str[i], tmp);
		i++;
	}
}
