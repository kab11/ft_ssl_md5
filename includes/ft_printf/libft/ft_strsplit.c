/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 22:05:11 by kblack            #+#    #+#             */
/*   Updated: 2018/08/27 20:37:18 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**ft_strsplit(char const *s, char c)
{
	int			i;
	int			k;
	char		**array;

	k = 0;
	if (!s || !c)
		return (NULL);
	i = ft_words(s, c);
	if (!(array = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	array[i] = NULL;
	while (s[i] != '\0')
	{
		while (*s == c && *s)
			s++;
		i = 0;
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
				i++;
			array[k++] = ft_mem_alloc(s, i);
			s += i;
		}
	}
	return (array);
}
