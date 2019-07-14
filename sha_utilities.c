/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 10:34:11 by kblack            #+#    #+#             */
/*   Updated: 2019/07/13 10:34:21 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		read_sha_stdin(int fd, t_sha *sh, char *input)
{
	char	buf[2];
	char	*str;
	char	*tmp;
	size_t	init_len;

	str = NULL;
	tmp = NULL;
	init_len = 0;
	buf[1] = '\0';
	while (read(fd, buf, 1))
	{
		if (str == NULL)
			str = ft_strdup(buf);
		else
		{
			tmp = str;
			str = ft_strjoin(tmp, buf);
			free(tmp);
		}
		init_len++;
	}
	sha_padding((uint8_t*)str, init_len, sh);
	sha_algo(sh);
	print_sha_hash(sh, input);
}
