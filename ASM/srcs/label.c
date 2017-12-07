/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenoit <ybenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 11:10:49 by ybenoit           #+#    #+#             */
/*   Updated: 2017/12/01 17:47:03 by gschaetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int			size_to_after(t_cmd *cmd, int begin, int end)
{
	t_cmd	*tmp;
	int		size;

	size = 0;
	tmp = give_this_link(&cmd, begin);
	while (tmp && tmp->place != end)
	{
		size += tmp->size;
		tmp = tmp->next;
	}
	return (size);
}

static int			size_to_before(t_cmd *cmd, int begin, int end)
{
	t_cmd	*tmp;
	int		size;

	size = 0;
	tmp = give_this_link(&cmd, begin);
	while (tmp && tmp->place != end)
	{
		size += tmp->size;
		tmp = tmp->next;
	}
	return ((unsigned int)(-size));
}

int					give_size_to_label(t_cmd *cmd, char *label, int place)
{
	int ret;
	int begin;
	int end;

	begin = place;
	end = find_this_label(cmd, label);
	if (begin < 0 || end < 0)
		return (-1);
	if (begin == end)
		return (0);
	else if (begin < end)
		return (size_to_after(cmd, begin, end));
	else
		return (size_to_before(cmd, end, begin));
}

void				init_label(t_cmd *cmd)
{
	int			i;
	t_cmd		*tmp;
	int			place;

	place = 0;
	tmp = cmd;
	while (tmp)
	{
		i = -1;
		while (++i < 3 && !tmp->label)
		{
			if (tmp->types[i] == -1 || !is_it_label(tmp->args[i]))
				tmp->label_name[0] = -1;
			else
			{
				tmp->arg_is_label[i] = 1;
				tmp->label_values[i] = give_size_to_label(cmd,
						tmp->args[i], tmp->place);
			}
		}
		tmp = tmp->next;
		place++;
	}
}

int					is_it_label(char *str)
{
	if (!str)
		return (0);
	if (str[0] && str[0] == ':')
	{
		str = ft_strcpy(str, str + 1);
		return (1);
	}
	else if (str[0] && str[1] && str[0] == '%' && str[1] == ':')
	{
		str = ft_strcpy(str, str + 2);
		return (1);
	}
	else
	{
		return (0);
	}
}
