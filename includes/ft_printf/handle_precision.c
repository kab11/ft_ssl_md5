/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 20:11:15 by kblack            #+#    #+#             */
/*   Updated: 2019/03/07 16:57:46 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		handle_precision(t_pf_token *pf, char **int_str)
{
	int		len;
	int		i;
	char	*temp;
	char	*new;

	len = (int)ft_strlen(*int_str);
	if (pf->flag.prec == 0 && *int_str[0] == '0')
		;
	else if (pf->flag.prec > len)
	{
		if (pf->ctype == 'o' && pf->flag.hash == 1)
			pf->flag.prec--;
		i = pf->flag.prec - len;
		temp = ft_strnew(i);
		while (i-- > 0)
			temp[i] = '0';
		new = ft_strjoin(temp, *int_str);
		free(*int_str);
		*int_str = new;
		free(temp);
	}
}
