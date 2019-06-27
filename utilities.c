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

int	check_file(char *name)
{
	struct stat	file_stats;

	if (lstat(name, &file_stats) == -1)
		return (-1);
	return (0);
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

void *ft_calloc(size_t count, size_t size)
{
	void *ret;
	size_t i;

	i = 0;
	if (!count || !size)
		return (NULL);
	ret = malloc(count * size);
	while (i <= count)
	{
		((char *)ret)[i] = 0x00;
		i++;
	}
	return (ret);
}
