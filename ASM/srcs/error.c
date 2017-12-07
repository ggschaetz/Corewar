/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenoit <ybenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 10:28:53 by ybenoit           #+#    #+#             */
/*   Updated: 2017/12/01 12:15:13 by gschaetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			syntax_error(t_cmd *cmd, t_files *file, t_cmd **head)
{
	ft_printf("Lexical error at ");
	print_token(cmd, file);
	secure_free(head, file, 1);
	exit(0);
}

char			*give_type_error(int type)
{
	if (type == 1)
		return ("register");
	else if (type == 2)
		return ("direct");
	else if (type == 4)
		return ("indirect");
	else
		return ("unknow");
}

void			type_error(t_cmd *cmd, t_files *file, t_cmd **head)
{
	ft_printf("Type error: OP[%s] at ", g_op_tab[cmd->hash_op].op);
	print_token_type(cmd, file);
	secure_free(head, file, 1);
	exit(0);
}

void			label_error(t_cmd *cmd, int label_error,
		t_files *file, t_cmd **head)
{
	cmd->error = label_error;
	ft_printf("Label error: no such label %s ", cmd->args[label_error]);
	if (cmd->types[label_error] == 4)
		ft_printf(": INDIRECT LABEL \":%s\" at ", cmd->args[label_error]);
	else
		ft_printf(": DIRECT LABEL \"%%:%s\" at ", cmd->args[label_error]);
	print_token(cmd, file);
	secure_free(head, file, 1);
	exit(0);
}
