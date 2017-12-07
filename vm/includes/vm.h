/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkantzer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 10:10:10 by mkantzer          #+#    #+#             */
/*   Updated: 2017/12/01 17:17:12 by mkantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# include <errno.h>
# include "../../includes/op.h"
# include "../../Libft/includes/ft_printf.h"
# include "../../Libft/includes/libft.h"
# include "../../Libft/includes/macro.h"

typedef struct			s_verb
{
	int					base;
	int					lives;
	int					cycles;
	int					op;
	int					deaths;
	int					pc;
}						t_verb;

typedef struct			s_champ
{
	int					pos;
	int					vm_pos;
	int					l_live;
	int					nb_lives;
	char				champ[CHAMP_MAX_SIZE + 1];
	t_header			*head;
	struct s_champ		*next;
	struct s_champ		*previous;
}						t_champ;

typedef struct			s_arena
{
	char				arena[MEM_SIZE];
	int					nb_player;
	int					nb_p;
	int					verbose;
	int					sum_lives;
	int					cur_cycle;
	int					die_cycle;
	int					dump;
	int					winner;
}						t_arena;

typedef struct			s_pc
{
	int					cur_pc;
	int					prev_pc;
	int					nb_octet;
}						t_pc;

typedef struct			s_process
{
	t_champ				*champ;
	int					pid;
	int					size_arg[3];
	int					value_arg[3];
	int					dir;
	int					ind;
	struct s_pc			*pc;
	int					l_live;
	int					nb_live;
	int					carry;
	int					r[REG_NUMBER];
	int					cur_op;
	int					ocp;
	int					prev_ocp;
	int					checkeur;
	int					cycle_less;
	int					cycle_to_go;
	int					fork;
	struct s_process	*previous;
	struct s_process	*next;
}						t_process;

typedef struct			s_op
{
	char				*name;
	int					param;
	int					size[3];
	int					op_code;
	int					cycles;
	char				*description;
	int					carry;
	int					ix;
	int					(*f)(t_process **p, t_arena **arena, t_verb **v);
}						t_op;

extern	t_op	g_op_tab[17];

/*
 **		main.c
*/

void					print_winner(t_arena **arena, t_champ **champ);

/*
 **		list.c
*/

void					add_champ(t_champ **champ, t_champ *new);
t_champ					*cr_champ(void);
void					add_process(t_process **pr, t_process *new);
t_process				*cr_process(t_champ **champ, int pid);
int						rip_process(t_process **p, t_arena **arena, t_verb **v);
void					free_champ(t_champ **champ, t_arena **arena);

/*
 **		init.c
*/

void					init_vm(t_arena **arena, t_champ **champ,\
		t_process **p);
void					init_champ(t_champ **champ);
void					init_v(t_verb **v, int nb);
void					free_all(t_arena **arena, t_process **p,\
		t_champ **champ, t_verb **v);

/*
 **		get_champ.c
*/

int						param_handler(int argc, char **argv, t_arena **arena,\
		t_champ **champ);
int						get_champ(char *argv, int pos, t_champ **lst,\
		t_arena **arena);
int						get_champ_head(t_champ **champ, int fd);
int						get_prog_size(t_champ **champ, int fd);

/*
 **		play.c
*/

int						pc_args(t_process **p, unsigned char c, int ix);
int						process_play(t_arena **arena, t_process **p,\
		t_verb **v);
int						cur_op(t_arena **arena, t_process **p);
int						play(t_arena **arena, t_process **p, t_verb **v);
int						check_process(t_process **p, t_arena **arena,\
		t_verb **v);
int						ctd_handler(t_arena **arena, t_process **p, t_verb **v,\
		int max);

/*
 **		tools.c
*/

uint32_t				big_to_little(uint32_t nb);
int						check_pos(t_champ **champ);
int						dash_handler(char **argv, int *i, t_arena **arena,\
		t_champ **champ);
int						dump_vm(t_arena **arena);
int						ret_print(t_champ **champ, int i);

/*
 **		tools_f.c
*/
void					arg_value(t_process **p, t_arena **arena, int tab_op);
int						n_dec(char *str);

/*
 **		print.c
*/

void					print_champ(t_champ *champ);
void					print_header(t_header head);
void					print_state(t_arena **arena);
void					print_p(t_process **p);
void					print_s_verb(t_verb **v);

/*
 **		verbose.c
*/

void					print_player(t_champ *champ, int i);
void					print_verb(t_process **p, t_arena **arena, int code);
void					print_pc(t_process **p, t_arena **arena);

/*
 **		print_p.c
*/

void					icmd_verb(int val1, int val2, int val3, t_process **p);
void					print_process(t_process **p, t_arena **arena);
void					three_params_verb(int val1, int val2, int val3,\
		t_process **p);
void					two_params_verb(int val1, int val2, t_process **p);
void					one_param_verb(int val1, t_process **p);
void					process_begin(t_process **p);

/*
 **		op_f.c
*/

int						m0d(int value, int mod);
int						live(t_process **p, t_arena **arena, t_verb **v);
int						st(t_process **p, t_arena **arena, t_verb **v);
int						ld(t_process **p, t_arena **arena, t_verb **v);
int						or(t_process **p, t_arena **arena, t_verb **v);
int						op_fork(t_process **p, t_arena **arena, t_verb **v);
int						zjmp(t_process **p, t_arena **arena, t_verb **v);
int						lldi(t_process **p, t_arena **arena, t_verb **v);
int						lfork(t_process **p, t_arena **arena, t_verb **v);
int						and(t_process **p, t_arena **arena, t_verb **v);
int						sti(t_process **p, t_arena **arena, t_verb **v);
int						xor(t_process **p, t_arena **arena, t_verb **v);
int						lld(t_process **p, t_arena **arena, t_verb **v);
int						sub(t_process **p, t_arena **arena, t_verb **v);
int						add(t_process **p, t_arena **arena, t_verb **v);
int						aff(t_process **p, t_arena **arena, t_verb **v);
int						ldi(t_process **p, t_arena **arena, t_verb **v);
t_process				*op_spe(t_process **p, t_process **tmp,\
		t_arena **arena, t_verb **v);
t_process				*op_lspe(t_process **p, t_process **tmp,\
		t_arena **arena, t_verb **v);
int						get_value_arena(t_arena **arena, int index, int idx);
void					put_value_arena(t_process **p, t_arena **arena,\
		int val1, int val2);
t_process				*hr_process(t_process **p, t_arena **arena,\
		int idx, int lfork);
void					fork_process(t_process **p, t_process *new);
/*
 **		checkeur.c
*/

int						checkeur(t_process **tmp, t_arena **arena, t_verb **v);
int						set_len(int val_arg, int len, int dir);
#endif
