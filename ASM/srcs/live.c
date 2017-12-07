/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschaetz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 15:18:35 by gschaetz          #+#    #+#             */
/*   Updated: 2017/10/25 14:18:55 by gschaetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		live_entier(t_cmd *tmp, int postion_arg)
{
	char	*buf;
	char	*zero;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	zero = ft_memalloc(8);
	buf = ft_itoabase(ft_atoi(tmp->args[0] + 1), 16);
	len = ft_strlen(buf);
	while (len > 8)
	{
		j++;
		len--;
	}
	while (i < 8 - len)
		zero[i++] = '0';
	buf = ft_strcpy(buf, buf + j);
	tmp->arg_bin[tmp->pos_arg_bin] = \
	ft_strcpy(tmp->arg_bin[tmp->pos_arg_bin], zero);
	tmp->arg_bin[tmp->pos_arg_bin] = \
	ft_strcat(tmp->arg_bin[tmp->pos_arg_bin], buf);
	tmp->bin = ft_strjoin_free(tmp->bin, zero);
	tmp->bin = ft_strjoin_free(tmp->bin, buf);
}

void		live_label(t_cmd *tmp, int postion_arg)
{
	char	*buf;
	char	*zero;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	zero = ft_memalloc(8);
	buf = ft_itoabase(tmp->label_values[postion_arg], 16);
	len = ft_strlen(buf);
	while (len > 8)
	{
		j++;
		len--;
	}
	while (i < 8 - len)
		zero[i++] = '0';
	buf = ft_strcpy(buf, buf + j);
	tmp->arg_bin[tmp->pos_arg_bin] = \
	ft_strcpy(tmp->arg_bin[tmp->pos_arg_bin], zero);
	tmp->arg_bin[tmp->pos_arg_bin] = \
	ft_strcat(tmp->arg_bin[tmp->pos_arg_bin], buf);
	tmp->bin = ft_strjoin_free(tmp->bin, zero);
	tmp->bin = ft_strjoin_free(tmp->bin, buf);
}
