/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschaetz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 11:33:32 by gschaetz          #+#    #+#             */
/*   Updated: 2017/12/01 14:39:21 by gschaetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		recup_reg(t_cmd *tmp, int postion_arg)
{
	char	*buf;
	int		i;
	int		j;
	int		len;
	char	*zero;

	i = 0;
	j = 0;
	zero = ft_memalloc(2);
	buf = ft_itoabase(ft_atoi(tmp->args[postion_arg] + 1), 16);
	len = ft_strlen(buf);
	while (i < 2 - len)
		zero[i++] = '0';
	len = i + len + 1;
	tmp->arg_bin[tmp->pos_arg_bin] = \
	ft_strcpy(tmp->arg_bin[tmp->pos_arg_bin], zero);
	tmp->arg_bin[tmp->pos_arg_bin] = \
	ft_strcat(tmp->arg_bin[tmp->pos_arg_bin], buf);
	tmp->bin = ft_strjoin_free(tmp->bin, zero);
	tmp->bin = ft_strjoin_free(tmp->bin, buf);
}

void		recup_entier(t_cmd *tmp, int postion_arg)
{
	char	*buff;
	char	*res;
	int		nb;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = ft_memalloc(4);
	res = ft_strcpy(res, tmp->args[postion_arg] + 1);
	buff = ft_itoabase(ft_atoi(res), 16);
	nb = ft_strlen(buff);
	if (nb > 4)
		j = nb - 4;
	while (i < 4 - nb && nb < 4)
		res[i++] = '0';
	while (i < 4)
		res[i++] = buff[j++];
	while (res[i])
		res[i++] = '\0';
	tmp->bin = ft_strjoin_free(tmp->bin, res);
	tmp->arg_bin[tmp->pos_arg_bin] = ft_strcpy(tmp->arg_bin[tmp->pos_arg_bin],\
	tmp->bin + ft_strlen(tmp->bin) - 4);
	free(buff);
}

void		recup_label(t_cmd *tmp, int postion_arg)
{
	int		nb;

	if (tmp->label_values[postion_arg] < 0)
	{
		nb = 0xffff + tmp->label_values[postion_arg] + 1;
		tmp->bin = ft_strjoin_free(tmp->bin, ft_itoabase(nb, 16));
		tmp->arg_bin[tmp->pos_arg_bin] = \
		ft_strjoin_free(tmp->arg_bin[tmp->pos_arg_bin], ft_itoabase(nb, 16));
	}
	else
		adressage_positif_label(tmp, postion_arg);
}

void		recup_index(t_cmd *tmp, int postion_arg)
{
	if (tmp->label_values[postion_arg] != 0)
		recup_label(tmp, postion_arg);
	else if (ft_strncmp(tmp->args[postion_arg], "r", 1) == 0)
	{
		tmp->bin = ft_strjoin_free(tmp->bin, "00");
		recup_reg(tmp, postion_arg);
		tmp->arg_bin[tmp->pos_arg_bin] = \
		ft_strjoin_free("00", tmp->arg_bin[tmp->pos_arg_bin]);
	}
	else if (ft_check_if_is_number(tmp->args[postion_arg]) == 1)
		recup_indirect(tmp, postion_arg);
	else
		recup_entier(tmp, postion_arg);
}

void		recup_dir(t_cmd *tmp, int postion_arg)
{
	char	buf[5];

	if (ft_strncmp(tmp->bin, "0b", 2) == 0 || \
			ft_strncmp(tmp->bin, "0c", 2) == 0 || \
			ft_strncmp(tmp->bin, "09", 2) == 0 || \
			ft_strncmp(tmp->bin, "0e", 2) == 0 || \
			ft_strncmp(tmp->bin, "0a", 2) == 0)
		recup_index(tmp, postion_arg);
	else if (ft_check_if_is_number(tmp->args[postion_arg]) == 1)
		recup_indirect(tmp, postion_arg);
	else if (tmp->types[postion_arg] == 4)
		recup_label(tmp, postion_arg);
	else
	{
		if (tmp->arg_is_label[postion_arg])
		{
			free(tmp->args[postion_arg]);
			tmp->args[postion_arg] = \
			ft_strjoin_free(ft_strcpy(ft_memalloc(2), "%\0"), \
					ft_itoa(tmp->label_values[postion_arg]));
			tmp->arg_is_label[postion_arg] = 0;
		}
		recup_direct_classic(tmp, postion_arg);
	}
}
