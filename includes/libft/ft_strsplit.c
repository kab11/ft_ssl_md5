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

static int		ft_wordlen(char const *str, char c)
{
	int				len;

	len = 0;
	while (str[len] != c && str[len] != '\0')
		len++;
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	char			**splits;
	int				word_count;
	int				i;
	int				j;

	if (s == NULL)
		return (0);
	word_count = ft_words(s, c);
	if (!(splits = (char **)malloc((sizeof(char *) * (word_count + 1)))))
		return (NULL);
	splits[word_count] = NULL;
	i = -1;
	j = 0;
	while (++i < word_count)
	{
		while (s[j] == c && s[j] != '\0')
			j++;
		splits[i] = ft_strsub(s + j, 0, ft_wordlen(s + j, c));
		j += ft_wordlen(s + j, c);
	}
	return (splits);
}
