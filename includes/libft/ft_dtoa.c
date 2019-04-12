/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 10:48:27 by kblack            #+#    #+#             */
/*   Updated: 2019/03/05 23:10:12 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_dtoa(intmax_t num)
{
	intmax_t	tmp;
	int			i;
	char		*str;

	i = 0;
	tmp = ft_labs(num);
	while (tmp > 0)
	{
		tmp /= 10;
		i++;
	}
	str = (char *)malloc(sizeof(char) * (i + 1));
	str[i] = '\0';
	i--;
	while (i >= 0)
	{
		str[i] = ft_labs(num) % 10 + '0';
		num /= 10;
		i--;
	}
	return (str);
}
