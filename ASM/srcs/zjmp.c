/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschaetz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 10:18:23 by gschaetz          #+#    #+#             */
/*   Updated: 2017/11/30 20:37:07 by gschaetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		zjmp_indirect(t_cmd *tmp, int postion_arg)
{
	char	*buf;
	char	*zero;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	zero = ft_memalloc(4);
	buf = ft_itoabase(ft_atoi(tmp->args[postion_arg] + 1), 16);
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

void		adressage_positif_label(t_cmd *tmp, int postion_arg)
{
	char	*buf;
	char	*zero;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	zero = ft_memalloc(4);
	buf = ft_itoabase(tmp->label_values[postion_arg], 16);
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
	tmp->bin = ft_strjoin_free(tmp->bin, zero);
	tmp->bin = ft_strjoin_free(tmp->bin, buf);
}
