/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_direct_classic.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschaetz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 16:29:12 by gschaetz          #+#    #+#             */
/*   Updated: 2017/12/01 12:42:26 by gschaetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		recup_entier_classic(t_cmd *tmp, int postion_arg)
{
	char	*buff;
	char	*res;
	int		nb;
	int		i;
	int		j;

	i = 1;
	j = 0;
	res = ft_memalloc(100);
	while (tmp->args[postion_arg][i])
		res[j++] = tmp->args[postion_arg][i++];
	j = 0;
	buff = ft_itoabase(ft_atoi(res), 16);
	nb = ft_strlen(buff);
	i = 0;
	while (i < 8 - nb)
		res[i++] = '0';
	while (i < 8)
		res[i++] = buff[j++];
	while (res[i])
		res[i++] = '\0';
	tmp->arg_bin[tmp->pos_arg_bin] = \
							ft_strcpy(tmp->arg_bin[tmp->pos_arg_bin], res);
	tmp->bin = ft_strjoin_free(tmp->bin, res);
	free(buff);
}

void		excpt_value_null(t_cmd *tmp, int postion_arg)
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

void		recup_direct_classic(t_cmd *tmp, int postion_arg)
{
	if (ft_strncmp(tmp->args[postion_arg], "r", 1) == 0\
			&& tmp->arg_is_label[postion_arg] != 1)
		recup_reg(tmp, postion_arg);
	else if (tmp->label_values[postion_arg] != 0\
			&& tmp->arg_is_label[postion_arg])
		recup_label(tmp, postion_arg);
	else if (tmp->label_values[postion_arg] == 0\
			&& tmp->arg_is_label[postion_arg])
		excpt_value_null(tmp, postion_arg);
	else
		recup_entier_classic(tmp, postion_arg);
}
