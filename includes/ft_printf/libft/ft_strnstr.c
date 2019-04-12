/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 12:02:41 by kblack            #+#    #+#             */
/*   Updated: 2018/08/27 19:00:00 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *str, const char *substr, size_t len)
{
	size_t sublen;

	if (*substr == '\0')
		return ((char *)str);
	sublen = ft_strlen(substr);
	while (*str && len >= sublen)
	{
		if (*str == *substr && ft_memcmp(str, substr, sublen) == 0)
			return ((char *)str);
		len--;
		str++;
	}
	return (NULL);
}
