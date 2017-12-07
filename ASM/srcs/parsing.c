/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenoit <ybenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 11:20:05 by ybenoit           #+#    #+#             */
/*   Updated: 2017/10/20 14:17:20 by ybenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char			*read_n_save(t_files *file)
{
	size_t		size_read;
	char		buf[sizeof(char) * 100000];

	file->file_str = (char*)secure_malloc(100000 * sizeof(char));
	size_read = read(file->input_fd, &buf, 100000);
	buf[size_read] = '\0';
	if (read(file->input_fd, &buf, 10000) > 0)
	{
		free(file->file_str);
		ft_printf("Don't send me shit please\n");
		exit(0);
	}
	if (ft_strstr(file->file_str, ".extend") != NULL)
	{
		free(file->file_str);
		ft_printf("I don't treat \'.extend\' files\n");
		exit(0);
	}
	ft_memcpy(file->file_str, buf, sizeof(char) * ft_strlen(buf));
	size_read = 0;
	return (file->file_str);
}

static void		parse_comment(t_files *file, char **line)
{
	int			i;
	char		*tmp;

	i = 0;
	tmp = ft_strchr(*line, '"') + 1;
	if (!file->n)
	{
		file->n = 1;
		if (ft_strlen_c(tmp, '"') > PROG_NAME_LENGTH)
			exit(ft_printf("champion name is too long (Max champion\
name len: 128)\n"));
		ft_strncpy(file->champ_name, tmp, ft_strlen_c(tmp, '"'));
		file->tmp = &tmp[ft_strlen_c(tmp, '"')];
	}
	else if (!file->c)
	{
		file->c = 1;
		if (ft_strlen_c(tmp, '"') > COMMENT_LENGTH)
			exit(ft_printf("comment is too long (Max comment len: 2048)\n"));
		tmp[ft_strlen_c(tmp, '"')] == '"' ? ft_memcpy(file->comment, tmp,
				ft_strlen_c(tmp, '"')) : exit(printf("Error on header\n"));
	}
	file->tmp++;
}

int				copy_at(char *dest, char *str, int index)
{
	int		i;

	i = 0;
	while (str[i])
		dest[index++] = str[i++];
	dest[index] = '\0';
	return (i);
}

void			init_head(t_files *file)
{
	file->tmp = file->file_str;
	file->n = 0;
	file->c = 0;
	ft_bzero((void*)file->champ_name, PROG_NAME_LENGTH);
	ft_bzero((void*)file->comment, COMMENT_LENGTH + 4);
	while (*file->tmp && *file->tmp <= ' ')
		file->tmp++;
	while (*file->tmp && !(file->c && file->n))
	{
		if (!ft_strncmp(".name ", file->tmp, 6) && !file->c)
			parse_comment(file, &file->tmp);
		else if (!ft_strncmp(".comment ", file->tmp, 9) && file->n)
			parse_comment(file, &file->tmp);
		if (file->c && file->n)
			break ;
		while (*file->tmp && *file->tmp == ' ')
			file->tmp++;
		if (*file->tmp && *file->tmp == '\n')
			file->tmp++;
		if ((*file->tmp && *file->tmp != '.') || !file->n)
			exit(ERROR_HEADER);
	}
	file->tmp++;
	if (!file->n || !file->c)
		exit(ERROR_HEADER);
}
