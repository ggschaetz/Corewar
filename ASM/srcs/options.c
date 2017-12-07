/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenoit <ybenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 10:29:52 by ybenoit           #+#    #+#             */
/*   Updated: 2017/11/30 14:16:42 by ybenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		print_cmd(t_cmd *tmp)
{
	int		i;
	char	*nb;

	i = 0;
	ft_printf("\t\t--------------------------------------\n");
	while (tmp->types[i] != -1 && tmp->args[i])
	{
		ft_printf("\t\t\033[31m%-8s\033[0m -> arg[%d] -> %-10s | \
type[%d] -> %s", tmp->arg_bin[i], i + 1,
tmp->args[i], tmp->types[i], give_type_error(tmp->types[i]));
		ft_printf("\n");
		i++;
	}
	if (g_op_tab[tmp->hash_op].ocp)
		ft_printf("\t\t--------------------------------------\n\t\tOCP = %x\n"
				, tmp->ocp);
}

void		print_line_to_bin(t_cmd *cmd, t_files *file)
{
	char *tmp;

	tmp = file->file_str + cmd->index;
	ft_printf("\t\t--------------------------------------\n");
	ft_putstr("\t\t");
	ft_printf("%s[%d] = \"", file->input_file, give_line(cmd, file));
	write(1, tmp, ft_strlen_c(tmp, '\n'));
	ft_printf("\" -> \033[31m%s\033[0m", cmd->bin);
	ft_putstr("\n");
}

void		print_chained(t_cmd *cmd, t_files *file)
{
	t_cmd	*tmp;
	char	*nb;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->label)
			ft_printf("\033[33mLABEL:\033[0m\n\t\"%s\"\t\tlink[%d]\n\
					\n\t{\n\t\t--size = %d && index = %d--\n",
					tmp->label_name, tmp->place, tmp->size, tmp->index);
		else
		{
			nb = ft_itoabase(g_op_tab[tmp->hash_op].code, 16);
			ft_printf("\033[32mOP:\n\t\033[0m %s --> \033[31m0%s\33[0m\t\tlink\
[%d]\t\thash_op[%d]\n\n\t{\n\t\tsize = %d at index = %d\n",
					g_op_tab[tmp->hash_op].op,
					nb, tmp->place,
					tmp->hash_op, tmp->size, tmp->index);
			free(nb);
			print_cmd(tmp);
			print_line_to_bin(tmp, file);
		}
		ft_printf("\t}\n\n\n");
		tmp = tmp->next;
	}
}
