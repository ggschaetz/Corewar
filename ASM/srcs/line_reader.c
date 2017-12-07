/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenoit <ybenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 10:29:27 by ybenoit           #+#    #+#             */
/*   Updated: 2017/12/05 12:41:07 by ybenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			cut_parse_this_line(char *str, int x, t_files *file, t_cmd *cmd)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[j] && str[j] > 33)
		j++;
	while (str[j] && str[j] < 33)
		str++;
	init_op_arg(cmd, str + j, file);
	while (cmd->args[i])
		i++;
	if (i != g_op_tab[x].nb_args)
		cmd->error = i;
	i = -1;
	while (++i < 3)
	{
		cmd->label_values[i] = 0;
		cmd->arg_is_label[i] = 0;
	}
}

t_cmd			*parse_this_line(char *str, int place, t_files *file)
{
	int		x;
	t_cmd	*cmd;

	cmd = secure_malloc(sizeof(t_cmd));
	cmd->index = file->index;
	x = 0;
	cmd->size = 0;
	cmd->label = 0;
	cmd->place = place;
	cmd->error = -1;
	while ((ft_strncmp(str, g_op_tab[x].op, ft_strlen_c(str, ' ')) != 0
			|| ft_strlen_c(str, ' ') != ft_strlen(g_op_tab[x].op))
			&& x < 15)
		x++;
	if ((x >= 15 && ft_strncmp("aff", str, 3)))
		return (check_label(cmd, str, file));
	cmd->error = (g_op_tab[x].nb_args - 1 != counting_coma(str)) ? 1 : -1;
	cut_parse_this_line(str, x, file, cmd);
	cmd->hash_op = x;
	if (g_op_tab[cmd->hash_op].ocp)
		init_encoding(cmd);
	else
		cmd->ocp = 0;
	give_size_cmd(cmd);
	return (cmd);
}

t_cmd			**add_link(t_cmd **head, t_cmd *to_add, t_files *file)
{
	t_cmd *tmp;

	if (!to_add->label)
		if (!to_add)
			return (head);
	if (!*head)
	{
		*head = to_add;
		return (head);
	}
	if (to_add->types[0] == -1)
		to_add->error = 0;
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = to_add;
	tmp->next->next = NULL;
	return (head);
}

t_cmd			*give_last(t_cmd **cmd)
{
	t_cmd *tmp;

	if (!cmd)
		return (NULL);
	tmp = *cmd;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_cmd			*parse_lines(t_cmd **cmd, t_files *file)
{
	t_cmd	*tmp;
	int		i;
	char	*line;

	i = 0;
	*cmd = NULL;
	init_index_begin_cmd(file);
	while (*file->tmp && file->tmp[3])
	{
		while (*file->tmp > 0 && *file->tmp < 33 && file->index++)
			file->tmp++;
		line = ft_strsub(file->tmp, 0, ft_strlen_c(file->tmp, '\n'));
		cmd = add_link(cmd, parse_this_line(line, i++, file), file);
		if (give_last(cmd)->label != 1)
			go_to_next_op(file);
		while (*file->tmp > 0 && *file->tmp < 33 && file->index++)
			file->tmp++;
		free(line);
		if (give_last(cmd)->error != -1)
			return (*cmd);
	}
	init_label(*cmd);
	return (*cmd);
}
