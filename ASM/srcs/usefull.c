/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usefull.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenoit <ybenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 10:30:18 by ybenoit           #+#    #+#             */
/*   Updated: 2017/10/20 14:03:41 by ybenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			nb_to_character(char *str, char *bin, int size)
{
	int			i;
	char		*bin_tmp;
	char		tmp[3];

	i = 0;
	bin_tmp = bin;
	while (*bin_tmp && size > 0)
	{
		ft_strncpy(tmp, bin_tmp, 2);
		str[i] = ft_atoi_base(tmp, 16);
		size--;
		i++;
		bin_tmp += 2;
	}
}

void			init_index_begin_cmd(t_files *file)
{
	char		*tmp;
	int			count;
	int			i;

	i = 0;
	tmp = file->file_str;
	count = 0;
	while (*tmp && count != 4)
	{
		if (*tmp == '"')
			count++;
		tmp++;
		file->index_begin_cmd++;
	}
	file->index = file->index_begin_cmd;
	file->tmp = file->file_str;
	file->tmp += file->index;
	while (file->tmp[i] && file->tmp[i] <= ' ')
		i++;
	if (!file->tmp[i])
	{
		ft_printf("Don't send me shit please\n");
		exit(0);
	}
}

void			give_size_cmd(t_cmd *cmd)
{
	int			i;

	i = 0;
	cmd->size = 0;
	if (cmd->label == 1)
	{
		cmd->size = 0;
		return ;
	}
	cmd->size += (g_op_tab[cmd->hash_op].ocp) ? 2 : 1;
	while (i < 3 && cmd->types[i] != -1)
	{
		if (cmd->types[i] != 2)
			cmd->size += (cmd->types[i] == 1) ? 1 : 2;
		else
			cmd->size += (g_op_tab[cmd->hash_op].i_or_d) ? 2 : 4;
		i++;
	}
}

int				find_this_label(t_cmd *cmd, char *label)
{
	t_cmd		*tmp;
	int			i;

	i = 0;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->label && !ft_strcmp(tmp->label_name, label))
			return (i);
		tmp = tmp->next;
		i++;
	}
	return (-1);
}

t_cmd			*give_this_link(t_cmd **cmd, int link)
{
	t_cmd		*tmp;

	tmp = *cmd;
	while (tmp)
	{
		if (tmp->place == link && tmp)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
