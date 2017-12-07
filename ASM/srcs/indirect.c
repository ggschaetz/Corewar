/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschaetz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 16:58:05 by gschaetz          #+#    #+#             */
/*   Updated: 2017/10/25 14:13:02 by gschaetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		recup_indirect(t_cmd *tmp, int postion_arg)
{
	char	*buf;
	char	*zero;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	zero = ft_memalloc(4);
	buf = ft_itoabase(ft_atoi(tmp->args[postion_arg]), 16);
	len = ft_strlen(buf);
	while (len > 4)
	{
		j++;
		len--;
	}
	while (i < 4 - len)
		zero[i++] = '0';
	buf = ft_strcpy(buf, buf + j);
	tmp->arg_bin[tmp->pos_arg_bin] = \
	ft_strcpy(tmp->arg_bin[tmp->pos_arg_bin], zero);
	tmp->arg_bin[tmp->pos_arg_bin] = \
	ft_strcat(tmp->arg_bin[tmp->pos_arg_bin], buf);
	tmp->bin = ft_strjoin_free(tmp->bin, ft_strjoin_free(zero, buf));
}
