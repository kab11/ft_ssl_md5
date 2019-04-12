/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 17:03:29 by kblack            #+#    #+#             */
/*   Updated: 2019/03/07 17:07:40 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_nan(t_pf_token *pf)
{
	if (pf->ctype == 'f')
		pf->out = write(1, "nan", 3);
	else
		pf->out = write(1, "NAN", 3);
}

void		print_inf(t_pf_token *pf)
{
	if (pf->ctype == 'f')
		pf->out = write(1, "inf", 3);
	else
		pf->out = write(1, "INF", 3);
}

long		get_decimal(long double num, int prec)
{
	int		sign;
	int		i;

	i = 0;
	sign = (num < 0) ? -1 : 1;
	num *= sign;
	while (i < prec)
	{
		num *= 10;
		i++;
	}
	num += 0.5;
	num *= sign;
	return ((long)num);
}

char		*handle_flt_prec(int dot, char *str, int len, t_pf_token *pf)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = ft_strnew(len + pf->flag.hash + 1);
	while (len >= 0)
	{
		if (i == dot && len > 0)
			tmp[j++] = '.';
		if (i > len)
		{
			tmp[j] = '\0';
			break ;
		}
		tmp[j++] = str[i];
		i++;
	}
	return (tmp);
}
