/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkantzer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 10:38:14 by mkantzer          #+#    #+#             */
/*   Updated: 2017/11/30 21:06:23 by mkantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		main(int argc, char **argv)
{
	t_champ		*champ;
	t_arena		*arena;
	t_process	*p;
	t_verb		*v;

	if (argc < 2 || !(param_handler(argc, argv, &arena, &champ)))
		return (0);
	init_vm(&arena, &champ, &p);
	ft_putendl("Introducing contestants...");
	print_player(champ, arena->nb_player + 1);
	v = ft_memalloc(sizeof(t_verb));
	if (arena->verbose != -1)
		init_v(&v, arena->verbose);
	if (play(&arena, &p, &v))
		print_winner(&arena, &champ);
	free_all(&arena, &p, &champ, &v);
	return (0);
}

void	print_winner(t_arena **arena, t_champ **champ)
{
	t_champ *tmp;

	tmp = *champ;
	if ((*arena)->winner == 0)
		(*arena)->winner = (*arena)->nb_player * -1;
	ft_printf("Contestant %i", (*arena)->winner * -1);
	while (tmp)
	{
		if (tmp->pos == (*arena)->winner)
			ft_printf(", \"%s\", has won !\n", tmp->head->prog_name);
		tmp = tmp->next;
	}
}
