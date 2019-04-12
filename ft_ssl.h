/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 16:07:28 by kblack            #+#    #+#             */
/*   Updated: 2019/04/05 14:03:53 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include "ft_printf.h"

/*
** Bit operations 
*/

# define BIT_ON(x, y) x |= y
# define BIT_OFF(x, y) x &= (~y)
# define BIT_FLIP(x, y) x ^= y

# define HASH_COUNT 1

/*
** Bit masks
*/

enum e_flag
{
	OPT_P = 1 << 0,
	OPT_Q = 1 << 1,
	OPT_R = 1 << 2,
	OPT_S = 1 << 3	
};

int		turn_on_flags(char **av);

#endif
