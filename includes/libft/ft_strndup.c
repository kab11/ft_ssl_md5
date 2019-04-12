/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 21:09:35 by kblack            #+#    #+#             */
/*   Updated: 2019/03/16 21:09:42 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strndup(char *src, size_t n)
{
	char			*dup;

	dup = (char *)malloc(sizeof(char) * (n + 1));
	if (dup)
	{
		ft_strncpy(dup, src, n);
		dup[n] = '\0';
	}
	return (dup);
}
