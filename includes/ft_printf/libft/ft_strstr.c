/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 10:18:01 by kblack            #+#    #+#             */
/*   Updated: 2018/08/27 19:00:34 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *str, const char *substr)
{
	int i;
	int j;

	i = 0;
	if (substr[i] == '\0')
		return ((char *)str);
	while (str[i])
	{
		j = 0;
		while (substr[j] == str[i + j])
		{
			if (substr[j + 1] == '\0')
			{
				return ((char *)str + i);
			}
			j++;
		}
		i++;
	}
	return (0);
}
