/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenoit <ybenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 10:29:36 by ybenoit           #+#    #+#             */
/*   Updated: 2017/12/01 14:37:38 by gschaetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void				del_com(char *str)
{
	char	*tmp;
	int		i;

	tmp = str;
	while (*tmp)
	{
		i = 0;
		if (*tmp == '#' || *tmp == ';')
		{
			while (*tmp && *(tmp + i) != '\n')
			{
				*(tmp + i) = ' ';
				i++;
			}
		}
		if (*tmp < ' ' && *tmp > 0 && *tmp != '\n')
			*tmp = ' ';
		tmp++;
	}
}

static int				find_or_create(t_files *file)
{
	if ((file->input_fd = open(file->input_file, O_RDONLY)) < 0)
		return (ERROR_OPEN);
	return (1);
}

void					asm_writter(t_cmd **cmd, t_files *file)
{
	char		*magic;

	magic = secure_malloc(sizeof(char) * 9);
	nb_to_character(magic, "00ea83f3", 4);
	write_in_output(*file, magic, 4);
	write_in_output(*file, file->champ_name, PROG_NAME_LENGTH);
	write_in_output(*file, file->champ_size, 8);
	write_in_output(*file, file->comment, COMMENT_LENGTH + 4);
	conversion_in_bin(cmd, *file);
	free(magic);
	printf("Writting output program to %s\n", file->output_file);
	secure_free(cmd, file, 0);
}

static void				asm_corewar(t_cmd **cmd, t_files *file)
{
	file->file_str = read_n_save(file);
	del_com(file->file_str);
	init_head(file);
	*cmd = parse_lines(cmd, file);
	init_champ_size(file, cmd);
	op_checker(*cmd, file, cmd);
	if (file->verbose)
	{
		conversion_in_bin_without_printing(cmd, *file);
		print_chained(*cmd, file);
		secure_free(cmd, file, 0);
		exit(0);
	}
	if ((file->output_fd = open(file->output_file, O_CREAT | O_WRONLY |
					O_APPEND | O_TRUNC, 0644)) < 0 && !file->verbose)
		exit(ERROR_CREATE);
	asm_writter(cmd, file);
}

int						main(int argc, char **argv)
{
	t_files		file;
	t_cmd		*cmd;

	if (argc < 2)
		return (USAGE_ASM);
	file.verbose = (argc == 3 && !ft_strcmp(argv[1], "-a")) ? 1 : 0;
	if (file.verbose)
		file.input_file = argv[2];
	else
	{
		file.input_file = argv[1];
		file.output_file = change_extension(argv[1]);
	}
	if ((find_or_create(&file)) != 1)
		return (0);
	asm_corewar(&cmd, &file);
	return (0);
}
