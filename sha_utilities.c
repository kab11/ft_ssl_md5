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

void		sha_pre_processing(t_sha *sh)
{
	sh->state[0] = 0x6a09e667;
	sh->state[1] = 0xbb67ae85;
	sh->state[2] = 0x3c6ef372;
	sh->state[3] = 0xa54ff53a;
	sh->state[4] = 0x510e527f;
	sh->state[5] = 0x9b05688c;
	sh->state[6] = 0x1f83d9ab;
	sh->state[7] = 0x5be0cd19;
}

void		read_sha_stdin(int fd, t_sha *sh, char *input)
{
	char	buf[2];
	char	*str;
	char	*tmp;
	uint64_t	init_len;

	str = NULL;
	tmp = NULL;
	init_len = 0;
	buf[1] = '\0';
	while (read(fd, buf, 1) > 0)
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
	// printf("string length = %zu\n", ft_strlen(str));
	sha_padding((uint8_t*)str, ft_strlen(str), sh);
	sha_algo(sh);
	print_sha_hash(sh, input);
}
