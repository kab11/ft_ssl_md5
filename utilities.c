/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 22:04:13 by kblack            #+#    #+#             */
/*   Updated: 2019/06/02 04:43:15 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <math.h>

int	check_file(char *file)
{
	struct stat	file_stats;

	if (lstat(file, &file_stats) != -1)
		return (0);
	printf("md5: %s: No such file or directory\n", file);
	return (-1);
}

int	check_dir(char *name)
{
	DIR			*d_stream;

	d_stream = opendir(name);
	if (d_stream == NULL)
		return (-1);
	closedir(d_stream);
	d_stream = NULL;
	return (0);
}

void				pre_processing(t_ssl *ms)
{
	ms->var[0] = 0x67452301;
	ms->var[1] = 0xefcdab89;
	ms->var[2] = 0x98badcfe;
	ms->var[3] = 0x10325476;
}

unsigned			convert_to_big_endian(unsigned n)
{
	return ((n << 24) | ((n << 8) & 0x00ff0000) | ((n >> 8) & 0x0000ff00) | (n >> 24));
}

void read_stdin_and_file(int fd, t_ssl *ms, char *input)
{
	char buf[2];
	char *str = NULL;
	char *tmp = NULL;
	size_t init_len = 0;

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
	md5_padding((uint8_t*)str, init_len, ms);
	md5_algo(ms);
	print_hash(ms, input);
}
