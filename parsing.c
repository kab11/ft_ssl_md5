/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 22:33:14 by kblack            #+#    #+#             */
/*   Updated: 2019/04/05 22:33:20 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		turn_on_flags(char **av)
{
	int	i;
	int	j;
	int	flags;
	int	count;

	i = 0;
	flags = 0;
	count = 0;
	(!isatty(0)) ? BIT_ON(flags, PIPE) : 0;
	while (av[++i])
	{
		j = 0;
		if (av[i][0] == '-')
		{
			while (av[i][++j])
			{
				av[i][j] == 'p' ? BIT_ON(flags, FLAG_P) : 0;
				av[i][j] == 'q' ? BIT_ON(flags, FLAG_Q) : 0;
				av[i][j] == 'r' ? BIT_ON(flags, FLAG_R) : 0;
				av[i][j] == 's' ? BIT_ON(flags, FLAG_S) : 0;
			}
			count++;
		}
	}
	return (flags);
}
