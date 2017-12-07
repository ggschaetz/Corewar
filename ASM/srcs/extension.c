/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenoit <ybenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 10:28:59 by ybenoit           #+#    #+#             */
/*   Updated: 2017/10/20 10:31:04 by ybenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char			*change_extension(char *file)
{
	char	*cor_file;
	int		i;

	i = 0;
	while (file[i] && file[i + 1])
	{
		if (file[i] == '.' && file[i + 1] == 's')
			break ;
		i++;
	}
	if (!(ft_strstr(file, ".s")) || !file[i])
		return (NULL);
	cor_file = ft_strnew(ft_strlen(file) + 3);
	cor_file = ft_strncpy(cor_file, file, i);
	cor_file = ft_strcat(cor_file, ".cor");
	return (cor_file);
}
