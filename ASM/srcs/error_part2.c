/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_part2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenoit <ybenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 10:56:59 by ybenoit           #+#    #+#             */
/*   Updated: 2017/10/20 11:05:50 by ybenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int				give_line(t_cmd *cmd, t_files *file)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (file->file_str[i] && i < cmd->index)
	{
		if (file->file_str[i] == '\n')
			j++;
		i++;
	}
	return (j);
}

int				give_arg_place(t_cmd *cmd, t_files *file, int line)
{
	int		i;
	int		count;
	int		j;

	i = cmd->index;
	j = 4;
	count = cmd->error;
	i += 4;
	while (file->file_str[i] && file->file_str[i] <= ' ')
	{
		i++;
		j++;
	}
	while (file->file_str[i] && count)
	{
		if (file->file_str[i] == ',')
			count--;
		j++;
		i++;
	}
	i++;
	return (j + 1);
}

void			print_token_type(t_cmd *cmd, t_files *file)
{
	ft_printf("[%d:%d] parameter %d type %s \"%s\"\n",
			give_line(cmd, file),
			give_arg_place(cmd, file, give_line(cmd, file)),
			cmd->error,
			give_type_error(cmd->types[cmd->error]),
			cmd->args[cmd->error]);
}

void			print_token(t_cmd *cmd, t_files *file)
{
	ft_printf("[%3.3d:%3.3d]\n", give_line(cmd, file), give_arg_place(cmd, file
				, give_line(cmd, file)));
}
