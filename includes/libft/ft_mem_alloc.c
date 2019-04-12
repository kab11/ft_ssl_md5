/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 20:31:11 by kblack            #+#    #+#             */
/*   Updated: 2018/08/27 20:38:22 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_mem_alloc(char const *str, size_t n)
{
	char	*mem;
	size_t	i;

	i = 0;
	if (!n || !str)
		return (NULL);
	mem = (char *)malloc(sizeof(char) * (n + 1));
	if (!mem)
		return (NULL);
	while (i < n)
	{
		mem[i] = str[i];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}
