/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 22:56:06 by kblack            #+#    #+#             */
/*   Updated: 2018/11/02 00:45:48 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list		*get_file(t_list **list, int fd)
{
	t_list			*current;

	current = *list;
	if (!current)
	{
		*list = ft_lstnew(NULL, fd);
		(*list)->content = ft_strnew(0);
		(*list)->content_size = fd;
		return (*list);
	}
	while (current != NULL)
	{
		if (current->content_size == (size_t)fd)
			return (current);
		current = current->next;
	}
	current = ft_lstnew(NULL, 0);
	current->content = ft_strnew(0);
	current->content_size = fd;
	ft_lstadd(list, current);
	return (current);
}

int					copy_until(char **src, char **line, char c)
{
	int				i;
	char			*holder;

	i = 0;
	while ((*src)[i] != '\0' && (*src)[i] != c)
		i++;
	if ((*src)[i] == c && i == 0)
	{
		*line = ft_strnew(0);
		holder = ft_strdup((*src) + 1);
	}
	else if (i > 0)
	{
		*line = ft_strsub((*src), 0, i);
		if ((*src)[i] == c)
			i++;
		holder = ft_strdup((*src) + i);
	}
	else
		return (0);
	free((*src));
	(*src) = holder;
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	int				n;
	static t_list	*list;
	char			buf[BUFF_SIZE + 1];
	char			*holder;
	t_list			*file;

	n = 0;
	if (fd < 0 || !line || BUFF_SIZE < 0)
		return (GNL_ERROR);
	bzero(buf, BUFF_SIZE + 1);
	file = get_file(&list, fd);
	while (ft_strchr(file->content, '\n') == NULL
		&& (n = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[n] = '\0';
		holder = ft_strjoin(file->content, buf);
		free(file->content);
		file->content = ft_strdup(holder);
		free(holder);
	}
	if (n < 0)
		return (GNL_ERROR);
	else if (copy_until((char **)(&file->content), line, '\n') == 0 && n == 0)
		return (0);
	return (1);
}
