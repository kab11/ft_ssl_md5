/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:57:16 by kblack            #+#    #+#             */
/*   Updated: 2019/03/28 21:36:35 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				token_setup(size_t pos, char *buf, char *str, char *token)
{
	pos = 0;
	buf = str;
	if (token)
	{
		free(token);
		token = NULL;
	}
	token = ft_strnew(ft_strlen(buf) + 1);
}

char				*ft_strtok(char *str, const char sep)
{
	int				i;
	static size_t	pos = 0;
	static char		*buf = 0;
	static char		*token = NULL;

	i = 0;
	if (str)
		token_setup(pos, buf, str, token);
	if (pos >= ft_strlen(buf) || !buf)
		return (0);
	ft_memset(token, 0, ft_strlen(buf) + 1);
	while (pos < ft_strlen(buf))
	{
		if (buf[pos] == sep)
		{
			pos++;
			return (token);
		}
		token[i] = buf[pos];
		i++;
		pos++;
	}
	return (token);
}
