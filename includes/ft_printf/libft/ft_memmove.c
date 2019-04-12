/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 09:38:38 by kblack            #+#    #+#             */
/*   Updated: 2018/08/27 18:53:06 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*strdst;
	char	*strsrc;
	size_t	i;

	i = -1;
	strsrc = (char *)src;
	strdst = (char *)dst;
	if (strsrc < strdst)
		while ((int)(--n) >= 0)
			*(strdst + n) = *(strsrc + n);
	else
		while (++i < n)
			*(strdst + i) = *(strsrc + i);
	return (strdst);
}
