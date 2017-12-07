/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenoit <ybenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 10:29:09 by ybenoit           #+#    #+#             */
/*   Updated: 2017/12/01 12:15:43 by gschaetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			cut_secure_free(t_cmd **cmd, t_files *file)
{
	if (!file->verbose)
	{
		free(file->output_file);
		if (file->champ_size)
			free(file->champ_size);
	}
	free(file->file_str);
}

void			free_tab_arg(t_cmd **cmd)
{
	int	i;

	i = 0;
	while (i < 4)
		free((*cmd)->arg_bin[i++]);
	free((*cmd)->arg_bin);
}

void			secure_free(t_cmd **cmd, t_files *file, int error)
{
	t_cmd	*tmp;
	int		i;

	tmp = *cmd;
	while (tmp)
	{
		if (!(*cmd)->label)
		{
			i = 0;
			while (i < 3 && (*cmd)->types[i] > 0)
			{
				if ((*cmd)->args[i] && (*cmd)->types[i] != -1)
					free((*cmd)->args[i]);
				i++;
			}
			if (!error)
				free_tab_arg(cmd);
			free((*cmd)->args);
			free((*cmd)->bin);
		}
		tmp = (*cmd)->next;
		free(*cmd);
		*cmd = tmp;
	}
	cut_secure_free(cmd, file);
}
