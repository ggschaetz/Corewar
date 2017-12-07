/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arive-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 16:29:52 by arive-de          #+#    #+#             */
/*   Updated: 2017/11/30 16:29:57 by arive-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/ft_printf.h"

void			*secure_malloc(size_t size)
{
	void	*ret;

	ret = (void*)malloc(size);
	if (!ret)
		exit(ft_printf("Allocation failed\n"));
	return (ret);
}
