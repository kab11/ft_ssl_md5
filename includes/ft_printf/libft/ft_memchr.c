/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 00:19:56 by kblack            #+#    #+#             */
/*   Updated: 2018/08/27 18:52:19 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*string;
	size_t			i;

	i = -1;
	while (++i < n)
	{
		if (((unsigned char *)str)[i] == (unsigned char)c)
		{
			string = &((unsigned char *)str)[i];
			return (string);
		}
	}
	return (NULL);
}
