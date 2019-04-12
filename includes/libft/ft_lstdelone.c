/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 18:40:52 by kblack            #+#    #+#             */
/*   Updated: 2018/08/27 18:50:35 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*currnode;
	t_list	*holder;

	holder = NULL;
	currnode = *alst;
	holder = currnode->next;
	del(currnode->content, currnode->content_size);
	free(currnode);
	currnode = holder;
	*alst = NULL;
}
