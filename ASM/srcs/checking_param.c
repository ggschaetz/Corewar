/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_param.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenoit <ybenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 11:06:44 by ybenoit           #+#    #+#             */
/*   Updated: 2017/12/05 12:14:32 by ybenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int				is_direct(char *str)
{
	int i;

	if (str[1] && str[1] == ':')
		return (1);
	else if (!str[1])
		return (0);
	i = (str[1] == '-') ? 2 : 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int				is_register(char *str)
{
	int			i;
	int			reg_value;

	i = 1;
	if (!(str + 1))
		return (0);
	reg_value = ft_atoi(str + 1);
	if (reg_value <= 0 || reg_value > REG_NUMBER)
		return (0);
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int				is_ind_number(char *str)
{
	int		i;

	i = (str[0] == '-') ? 1 : 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int				is_good_arg(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] <= ' ')
		i++;
	while (str[i] && str[i] > ' ')
		i++;
	while (str[i] && str[i] <= ' ')
		i++;
	if (str[i] && str[i] != '\n')
		return (0);
	else
		return (1);
}
