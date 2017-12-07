/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkantzer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 17:28:58 by mkantzer          #+#    #+#             */
/*   Updated: 2017/12/05 13:59:01 by mkantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

uint32_t	big_to_little(uint32_t nb)
{
	uint32_t		res;
	uint32_t		b0;
	uint32_t		b1;
	uint32_t		b2;
	uint32_t		b3;

	b0 = (nb & 0x000000ff) << 24;
	b1 = (nb & 0x0000ff00) << 8;
	b2 = (nb & 0x00ff0000) >> 8;
	b3 = (nb & 0xff000000) >> 24;
	res = b0 | b1 | b2 | b3;
	return (res);
}

int			check_pos(t_champ **champ)
{
	t_champ		*tmp;
	t_champ		*tmp2;
	int			i;

	i = 0;
	tmp = *champ;
	while (tmp)
	{
		if (i >= 4)
			return (ret_print(champ, 1));
		tmp2 = *champ;
		while (tmp2)
		{
			if (tmp->pos == tmp2->pos && \
					tmp->head->prog_name != tmp2->head->prog_name)
			{
				ft_putendl("Position conflict");
				return (0);
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
		i++;
	}
	return (1);
}

int			dash_handler(char **argv, int *i, t_arena **arena, t_champ **champ)
{
	if ((!(ft_strcmp(argv[*i], "-dump")) || !(ft_strcmp(argv[*i], "-d")))\
			&& argv[*i + 1])
		(*arena)->dump = ft_atoi(argv[++(*i)]);
	if (!(ft_strcmp(argv[*i], "-v")) && argv[*i + 1])
		(*arena)->verbose = ft_atoi(argv[++(*i)]);
	if (!(ft_strcmp(argv[*i], "-n")) && argv[*i + 1])
	{
		if (ft_isdigit(argv[(*i) + 1][0]))
		{
			if (ft_atoi(argv[(*i) + 1]) > 0)
				get_champ(argv[(*i) + 2], ft_atoi(argv[(*i) + 1]),\
						champ, arena);
			else
			{
				free(*arena);
				ft_putendl("Position overflow");
				exit(0);
			}
		}
		else
			get_champ(argv[(*i) + 1], (*arena)->nb_player + 1, champ, arena);
		*i += 2;
	}
	return (0);
}

int			ret_print(t_champ **champ, int i)
{
	if (i == 1)
		ft_putendl("Too many champions. See './corewar -help'");
	else if (i == 2)
		ft_putendl("Uncorrect header.");
	else if (i == 3)
		ft_putendl("Champion access error.");
	else if (i == 4)
		ft_putendl("Champion too big.");
	else if (i == 5)
		ft_putendl("Position conflict");
	else if (i == 6)
		ft_putendl("[-dump] invalid");
	else if (i == 7)
		ft_putendl("[-n] invalid");
	free(*champ);
	free((*champ)->head);
	return (0);
}

int			dump_vm(t_arena **arena)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	ft_printf("0x0000 : ");
	while (i < MEM_SIZE)
	{
		if ((j % 65) == 0)
		{
			ft_putchar('\n');
			ft_printf("%#.4x : ", i);
			j = 1;
		}
		if ((*arena)->arena[i] == 0)
			ft_putstr("00 ");
		else
			ft_printf("%.2hhx ", (*arena)->arena[i]);
		j++;
		i++;
	}
	ft_putchar('\n');
	return (0);
}
