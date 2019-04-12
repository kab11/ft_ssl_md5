/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 23:14:58 by kblack            #+#    #+#             */
/*   Updated: 2018/08/27 18:52:06 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *cpy, const void *src, int c, size_t len)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;
	size_t			i;

	tmp1 = (unsigned char *)cpy;
	tmp2 = (unsigned char *)src;
	i = 0;
	c = (unsigned char)c;
	while (i < len)
	{
		if ((*tmp1++ = *tmp2++) == c)
			return (tmp1);
		i++;
	}
	return (NULL);
}
