/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenoit <ybenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 14:42:55 by ybenoit           #+#    #+#             */
/*   Updated: 2017/12/01 14:43:35 by ybenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H
# define MACRO_H

# define MAX(x, y)   ((x) >= (y) ? (x) : (y))
# define MIN(x, y)   ((x) <= (y) ? (x) : (y))
# define ABS(x)   ((x) < 0 ? (-(x)) : (x))
# define NINT(x)   ((x) < 0 ? ((long)(x-0.5)) : ((long)(x+0.5)))
# define SQ(x)   ((x) * (x))
# define MALLOC_ERROR exit(ft_printf("Allocation error"))
# define ERROR_CODE 666
# define EXIT_ERROR exit(ERROR_CODE)
# define TRUE 1
# define FALSE 0

#endif
