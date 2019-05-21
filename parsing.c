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

int turn_on_flags(char **av, t_ssl *ms)
{
	int i;
	int j;
	int flags;
	int count;

	i = 1;
	flags = 0;
	count = 0;
	while (av[i])
	{
		j = 1;
		if (av[i][0] == '-')
		{
			while (av[i][j])
			{
				printf("av[%d][%d] = %c\n", i, j, av[i][j]);
				av[i][j] == 'p' ? BIT_ON(flags, OPT_P) : 0;
				av[i][j] == 'q' ? BIT_ON(flags, OPT_Q) : 0;
				av[i][j] == 'r' ? BIT_ON(flags, OPT_R) : 0;
				av[i][j] == 's' ? BIT_ON(flags, OPT_S) : 0;
				j++;
			}
			count++;
		}
		i++;
	}
	ms->flag |= flags;
	return (count + 1);
}