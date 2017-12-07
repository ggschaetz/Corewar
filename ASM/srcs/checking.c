/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenoit <ybenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 10:28:40 by ybenoit           #+#    #+#             */
/*   Updated: 2017/12/05 12:15:26 by ybenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void		cut_op_checker(t_cmd *tmp, t_files *file, t_cmd **head)
{
	int i;

	i = 0;
	while (g_op_tab[tmp->hash_op].type[i] != 0)
	{
		if (((tmp->types[i] & g_op_tab[tmp->hash_op].type[i]) != \
					tmp->types[i]) || tmp->types[i] == -1)
		{
			tmp->error = i;
			type_error(tmp, file, head);
		}
		if (tmp->label_values[i] == -1)
			label_error(tmp, i, file, head);
		i++;
	}
	if ((tmp->types[i] != -1 || tmp->args[i]) && i < 3)
	{
		tmp->error = i;
		type_error(tmp, file, head);
	}
}

void			op_checker(t_cmd *cmd, t_files *file, t_cmd **head)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->error != -1)
			syntax_error(tmp, file, head);
		if (!tmp->label)
			cut_op_checker(tmp, file, head);
		tmp = tmp->next;
	}
}

int				counting_coma(char *str)
{
	int			i;
	int			ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == ',')
			ret++;
		i++;
	}
	return (ret);
}
