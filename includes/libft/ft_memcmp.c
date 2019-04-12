/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 09:04:09 by kblack            #+#    #+#             */
/*   Updated: 2018/08/27 18:52:28 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1cmp;
	unsigned char	*s2cmp;
	size_t			i;

	i = -1;
	s1cmp = (unsigned char *)s1;
	s2cmp = (unsigned char *)s2;
	while (++i < n && *(s1cmp + i) == *(s2cmp + i))
		;
	if (i == n)
		return (0);
	return (*(s1cmp + i) - *(s2cmp + i));
}
