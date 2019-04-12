/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 22:13:17 by kblack            #+#    #+#             */
/*   Updated: 2019/03/07 16:56:35 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Recode the printf function
** learn how to use variadic functions
*/

void			print_conversion(const char *fmt, va_list ap, t_pf_token *pf)
{
	ft_bzero(&pf->flag, sizeof(pf->flag));
	pf->i++;
	get_flags(fmt, pf);
	if (pf->flag.zero == 1 && pf->flag.left == 1)
		pf->flag.zero = 0;
	get_type(fmt, ap, pf);
	pf->i++;
}

int				ft_printf(const char *fmt, ...)
{
	t_pf_token	pf;
	va_list		ap;

	ft_bzero(&pf, sizeof(pf));
	va_start(ap, fmt);
	while (fmt[pf.i] != '\0')
	{
		if (fmt[pf.i] == '%' && fmt[pf.i + 1] == '%')
		{
			pf.out += write(1, "%", 1);
			pf.i += 2;
		}
		else if (fmt[pf.i] == '%' && fmt[pf.i + 1] != '%')
			print_conversion(fmt, ap, &pf);
		else
			pf.out += write(1, &fmt[pf.i++], 1);
	}
	va_end(ap);
	return (pf.out);
}
