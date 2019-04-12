/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 22:00:47 by kblack            #+#    #+#             */
/*   Updated: 2018/08/27 18:50:21 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*currnode;
	t_list	*holder;

	holder = NULL;
	currnode = *alst;
	while (currnode)
	{
		holder = currnode->next;
		del(currnode->content, currnode->content_size);
		free(currnode);
		currnode = holder;
	}
	*alst = NULL;
}
