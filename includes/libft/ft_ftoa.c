/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 21:54:48 by kblack            #+#    #+#             */
/*   Updated: 2019/03/05 23:15:26 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_ftoa(long double num)
{
	char	*str;
	int		i;
	int		sign;
	long	tmp;

	sign = (num < 0) ? -1 : 1;
	i = (num < 0) ? 1 : 0;
	num *= sign;
	tmp = (long)num;
	while (tmp > 0 && i++ >= 0)
		tmp /= 10;
	while (num - (long)num != 0 && i++ >= 0)
		num *= 10;
	str = ft_strnew(i + 1);
	while (i-- >= 0)
	{
		str[i] = (long)num % 10 + '0';
		num /= 10;
		if (sign == -1 && i == 1)
		{
			str[0] = '-';
			break ;
		}
	}
	return (str);
}
