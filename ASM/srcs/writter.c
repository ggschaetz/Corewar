/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenoit <ybenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 10:30:24 by ybenoit           #+#    #+#             */
/*   Updated: 2017/10/20 10:30:25 by ybenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			write_in_output(t_files file, char *buf, int len)
{
	write(file.output_fd, buf, len);
}
