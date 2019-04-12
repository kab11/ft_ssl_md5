/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 14:44:09 by kblack            #+#    #+#             */
/*   Updated: 2018/08/27 18:52:42 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcpy(void *cpy, const void *src, size_t n)
{
	char	*strcpy;
	char	*strsrc;
	size_t	i;

	strcpy = (char *)cpy;
	strsrc = (char *)src;
	i = 0;
	while (i < n)
	{
		*strcpy++ = *strsrc++;
		i++;
	}
	return (cpy);
}
