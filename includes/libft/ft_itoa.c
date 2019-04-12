/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 23:16:21 by kblack            #+#    #+#             */
/*   Updated: 2018/08/27 21:19:39 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_itoa(int n)
{
	char			*str;
	size_t			len;
	unsigned int	copy;

	len = ft_int_len(n);
	copy = n;
	if (n < 0)
	{
		copy = -n;
		len++;
	}
	str = ft_strnew(len);
	if (!str)
		return (NULL);
	len--;
	str[len] = copy % 10 + '0';
	while (copy /= 10)
		str[--len] = copy % 10 + '0';
	if (n < 0)
		*(str + 0) = '-';
	return (str);
}
