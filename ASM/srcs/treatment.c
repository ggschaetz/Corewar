/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenoit <ybenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 10:30:13 by ybenoit           #+#    #+#             */
/*   Updated: 2017/10/20 11:25:35 by ybenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			init_encoding(t_cmd *cmd)
{
	int i;
	int j;

	j = 0;
	i = 3;
	cmd->ocp = 0;
	while (j < 3 && cmd->types[j] != -1)
	{
		cmd->ocp += (cmd->types[j] != 4) ? cmd->types[j] << (i * 2) :
			(cmd->types[j] - 1) << (i * 2);
		i--;
		j++;
	}
}

int				give_bin_size(uintmax_t nb)
{
	int			decal;
	uintmax_t	bin_;
	int			count;

	decal = 56;
	count = 0;
	bin_ = 1837468647967162400;
	while (bin_ != 0)
	{
		if ((nb & bin_) > 0)
			count++;
		bin_ = bin_ >> 8;
		decal -= 8;
	}
	return (count);
}

void			cut_init_champ_size(char *tmp_str, t_files *file, int i,
		char *str)
{
	while (*tmp_str && i < 16)
	{
		file->champ_size[i] = *tmp_str;
		i++;
		tmp_str++;
	}
	if (str)
		free(str);
}

void			init_champ_size(t_files *file, t_cmd **cmd)
{
	t_cmd	*tmp;
	int		champ_size;
	int		i;
	char	*str;
	char	*tmp_str;

	tmp = *cmd;
	i = 0;
	champ_size = 0;
	while (tmp)
	{
		if (!tmp->label)
			champ_size += tmp->size;
		tmp = tmp->next;
	}
	file->champ_size = secure_malloc(sizeof(char) * 16);
	ft_memset((void*)file->champ_size, 48, sizeof(char) * 16);
	str = ft_itoabase(champ_size, 16);
	i = 16 - ft_strlen(str);
	tmp_str = str;
	cut_init_champ_size(tmp_str, file, i, str);
	nb_to_character(file->champ_size, file->champ_size, 8);
}
