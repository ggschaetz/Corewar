/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_champ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkantzer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 14:10:20 by mkantzer          #+#    #+#             */
/*   Updated: 2017/12/05 11:23:06 by arive-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		param_handler(int argc, char **argv, t_arena **arena, t_champ **champ)
{
	int i;

	i = 1;
	if (!(*arena = ft_memalloc(sizeof(t_arena))))
		return (0);
	(*arena)->dump = -1;
	(*arena)->verbose = -1;
	(*arena)->nb_player = 0;
	while (i < argc)
	{
		if ((i + 1 < argc) && argv[i][0] == '-')
			dash_handler(argv, &i, arena, champ);
		else
			get_champ(argv[i], (*arena)->nb_player + 1, champ, arena);
		i++;
	}
	if (!(check_pos(champ)) || (*arena)->nb_player == 0)
	{
		free_champ(champ, arena);
		return (0);
	}
	return (1);
}

int		get_champ(char *file, int pos, t_champ **lst, t_arena **arena)
{
	t_champ		*champ;
	uint32_t	ret;
	int			fd;

	champ = cr_champ();
	init_champ(&champ);
	(*champ).pos = pos * -1;
	if ((fd = open(file, O_RDONLY)) < 0)
		return (ret_print(&champ, 3));
	if (!(get_champ_head(&champ, fd)))
		return (0);
	if (read(fd, champ->champ, 4) < 0)
		return (ret_print(&champ, 3));
	ret = read(fd, &champ->champ, CHAMP_MAX_SIZE + 1);
	if (ret != champ->head->prog_size)
		return (ret_print(&champ, 4));
	close(fd);
	add_champ(lst, champ);
	(*arena)->nb_player++;
	return (1);
}

int		get_champ_head(t_champ **champ, int fd)
{
	uint32_t	magic;

	magic = 0;
	if (read(fd, &magic, 4) < 0)
		return (ret_print(champ, 3));
	magic = big_to_little(magic);
	if (magic != COREWAR_EXEC_MAGIC)
		return (0);
	(*champ)->head->magic = magic;
	if (read(fd, (*champ)->head->prog_name, PROG_NAME_LENGTH) < 0)
		return (ret_print(champ, 3));
	if (!(get_prog_size(champ, fd)))
		return (0);
	if (read(fd, (*champ)->head->comment, COMMENT_LENGTH) < 0)
		return (ret_print(champ, 3));
	return (1);
}

int		get_prog_size(t_champ **champ, int fd)
{
	uint32_t	prog_size;

	if (read(fd, &prog_size, 4) < 0)
		return (ret_print(champ, 3));
	if (read(fd, &prog_size, 4) < 0)
		return (ret_print(champ, 3));
	prog_size = big_to_little(prog_size);
	if (prog_size > CHAMP_MAX_SIZE)
		return (ret_print(champ, 4));
	(*champ)->head->prog_size = prog_size;
	return (1);
}
