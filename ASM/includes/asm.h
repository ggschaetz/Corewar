/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenoit <ybenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 11:55:32 by ybenoit           #+#    #+#             */
/*   Updated: 2017/12/05 12:10:47 by ybenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../../Libft/includes/libft.h"
# include "../../Libft/includes/ft_printf.h"
# include "../../Libft/includes/macro.h"
# include "../../includes/op.h"

# define USAGE_ASM ft_printf("usage: ./asm file.s\n")
# define ERROR_OPEN ft_printf("Error: Can't open file\n")
# define ERROR_CREATE ft_printf("Error: Can't create file\n")
# define ERROR_HEADER ft_printf("Error on header\n")
# define ERROR_MALLOC ft_printf("Allocation error\n")
# define HEADER_END PROG_NAME_LENGTH + COMMENT_LENGTH + 3

typedef struct			s_files
{
	int					input_fd;
	int					output_fd;
	char				*input_file;
	char				*output_file;
	int					index;
	char				*buf;
	int					c;
	char				champ_name[PROG_NAME_LENGTH];
	int					n;
	char				comment[COMMENT_LENGTH + 4];
	char				*file_str;
	char				*tmp;
	int					index_begin_cmd;
	int					verbose;
	char				*champ_size;
}						t_files;

typedef struct			s_cmd
{
	int					place;
	int					label;
	char				label_name[1500];
	int					hash_op;
	int					nb_args;
	char				**args;
	int					arg_is_label[3];
	int					label_values[3];
	int					types[3];
	int					error;
	int					ocp;
	char				**arg_bin;
	int					pos_arg_bin;
	int					size;
	int					index;
	char				*bin;
	struct s_cmd		*next;
}						t_cmd;

typedef struct			s_to_bin
{
	int					hash_op;
	char				*(*f)(t_cmd *cmd);
}						t_to_bin;

typedef struct			s_op
{
	char				*op;
	char				nb_args;
	char				type[MAX_ARGS_NUMBER];
	char				code;
	int					nb_cycles;
	char				*comment;
	int					ocp;
	int					i_or_d;
}						t_op;

extern t_op				g_op_tab[17];
int						counting_coma(char *str);
void					go_to_next_op(t_files *file);
t_cmd					*check_label(t_cmd *cmd, char *str, t_files *file);
void					init_op_arg(t_cmd *cmd, char *str, t_files *file);
int						check_number_param(int x, char *str);
char					*read_n_save(t_files *file);
int						give_arg_place(t_cmd *cmd, t_files *file, int line);
int						is_good_arg(char *str);
void					print_token_type(t_cmd *cmd, t_files *file);
char					*change_extension(char *file);
void					write_in_output(t_files file, char *buf, int len);
void					init_head(t_files *file);
int						copy_at(char *dest, char *str, int index);
int						give_bin_size(uintmax_t nb);
void					nb_to_character(char *str, char *bin, int size);
t_cmd					*parse_lines(t_cmd **cmd, t_files *file);
t_cmd					*parse_this_line(char *str, int place, t_files *file);
void					init_encoding(t_cmd *cmd);
void					init_index_begin_cmd(t_files *file);
void					give_size_cmd(t_cmd *cmd);
t_cmd					*give_this_link(t_cmd **cmd, int link);
int						find_this_label(t_cmd *cmd, char *label);
int						give_size_to_label(t_cmd *cmd, char *label, int place);
int						is_it_label(char *str);
int						is_direct(char *str);
int						is_register(char *str);
int						is_ind_number(char *str);
void					init_label(t_cmd *cmd);
void					op_checker(t_cmd *cmd, t_files *file, t_cmd **head);
void					syntax_error(t_cmd *cmd, t_files *file, t_cmd **head);
void					type_error(t_cmd *cmd, t_files *file, t_cmd **head);
void					label_error(t_cmd *cmd, int label_error, t_files *file
						, t_cmd **head);
void					print_token(t_cmd *cmd, t_files *file);
void					print_chained(t_cmd *cmd, t_files *file);
int						give_line(t_cmd *cmd, t_files *file);
void					conversion_in_bin(t_cmd **cmd, t_files file);
void					conversion_in_bin_without_printing(t_cmd **cmd,
						t_files file);
char					*give_type_error(int types);
void					init_champ_size(t_files *file, t_cmd **cmd);
void					recup_reg(t_cmd *tmp, int position_arg);
void					recup_dir(t_cmd *tmp, int position_arg);
char					*recup_ind(t_cmd *tmp, int position_arg);
void					recup_label(t_cmd *tmp, int position_arg);
void					recup_direct_classic(t_cmd *tmp, int position_arg);
void					fork_zjmp_live_in_bin(t_cmd *tmp, int position_arg);
void					live_entier(t_cmd *tmp, int position_arg);
void					live_label(t_cmd *tmp, int position_arg);
void					recup_indirect(t_cmd *tmp, int position_arg);
void					adressage_positif_label(t_cmd *tmp, int position_arg);
int						ft_check_if_is_number(char *str);
void					zjmp_indirect(t_cmd *tmp, int position_arg);
void					secure_free(t_cmd **cmd, t_files *file, int error);
char					**ft_malloc_tab(int x, int y);
#endif
