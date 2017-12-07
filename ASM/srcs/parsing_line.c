/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenoit <ybenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 11:29:29 by ybenoit           #+#    #+#             */
/*   Updated: 2017/12/05 12:46:28 by ybenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			go_to_next_op(t_files *file)
{
	file->index += ft_strlen_c(file->tmp, '\n');
	file->tmp += ft_strlen_c(file->tmp, '\n');
}

int				give_type(char *str)
{
	int			i;

	i = 0;
	while (str[i] && str[i] < 33)
		i++;
	if (!str[i])
		return (-1);
	if (str[i] == 'r' && is_register(str + i))
		return (1);
	else if (str[i] == '%' && is_direct(str + i))
		return (2);
	else if (str[i] == ':' || is_ind_number(str + i))
		return (4);
	else if (!str[i])
		return (-1);
	else
		return (5);
}

void			check_too_much_param(t_cmd *cmd)
{
	int			i;

	i = -1;
	while (cmd->args[++i])
	{
		cmd->types[i] = give_type(cmd->args[i]);
		if (cmd->types[i] == 5)
			cmd->error = i;
		if (i == 3)
			cmd->error = 3;
	}
}

void			init_op_arg(t_cmd *cmd, char *str, t_files *file)
{
	int			i;

	i = -1;
	if (ft_strlen_c(str, '\n') > 30)
		exit(ft_printf("U're a NAZI\n"));
	cmd->args = ft_strsplit(str, ',');
	while (cmd->args[++i])
		if (!is_good_arg(cmd->args[i]))
		{
			cmd->error = i;
			return ;
		}
	i = -1;
	del_space(cmd->args);
	while (++i < 3)
		cmd->types[i] = -1;
	i = -1;
	if (!cmd->args[0])
	{
		cmd->error = 0;
		return ;
	}
	check_too_much_param(cmd);
}

t_cmd			*check_label(t_cmd *cmd, char *str, t_files *file)
{
	int			i;

	i = 0;
	while (*str && *str < 33)
		str++;
	while (str[i] && ft_strchr(LABEL_CHARS, str[i]))
		i++;
	if (str[i] != ':' || (str[i + 1] &&
				(str[i + 1] != ' ' && str[i + i] > ' ')))
		cmd->error = 0;
	cmd->label = 1;
	if (ft_strlen_c(str, ':') > 1499)
	{
		ft_printf("U're a NAZI.\n");
		exit(0);
	}
	ft_strncpy(cmd->label_name, str, ft_strlen_c(str, ':'));
	while (*str && *str != ':')
		str++;
	str++;
	file->tmp += ft_strlen(cmd->label_name) + 1;
	file->index += ft_strlen(cmd->label_name) + 1;
	cmd->hash_op = 'l';
	return (cmd);
}
