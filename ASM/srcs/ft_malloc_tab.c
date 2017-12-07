/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschaetz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 11:16:22 by gschaetz          #+#    #+#             */
/*   Updated: 2017/10/25 11:56:25 by gschaetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char		**ft_malloc_tab(int x, int y)
{
	int		i;
	char	**tab;

	i = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * x)))
		return (NULL);
	while (i < x)
		tab[i++] = ft_memalloc(y);
	tab[i] = NULL;
	return (tab);
}
