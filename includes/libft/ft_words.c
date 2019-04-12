/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_words.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 20:28:41 by kblack            #+#    #+#             */
/*   Updated: 2018/08/27 20:38:08 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_words(char const *str, const char ch)
{
	const char	*string;
	int			i;
	int			wc;

	string = str;
	i = 0;
	wc = 0;
	while (string[i] != '\0')
	{
		if (string[i] == ch)
			i++;
		if (string[i] != ch && string[i])
		{
			wc++;
			while (string[i] != ch && string[i])
				i++;
		}
	}
	return (wc);
}
