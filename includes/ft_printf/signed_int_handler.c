/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signed_int_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 15:32:43 by kblack            #+#    #+#             */
/*   Updated: 2019/03/07 17:18:22 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t		find_int_size(va_list ap, t_pf_token *pf)
{
	intmax_t	length;

	if (pf->u.ll)
		length = (intmax_t)va_arg(ap, long long);
	else if (pf->u.l)
		length = (intmax_t)va_arg(ap, long);
	else if (pf->u.hh)
		length = (intmax_t)(char)va_arg(ap, int);
	else if (pf->u.h)
		length = (intmax_t)va_arg(ap, int);
	else
		length = (intmax_t)va_arg(ap, int);
	return (length);
}

void			print_int(va_list ap, t_pf_token *pf)
{
	intmax_t	num;
	int			sign;
	char		*int_str;

	num = find_int_size(ap, pf);
	pf->s.num = num;
	if (num == LONG_MIN || num == LLONG_MIN)
		int_str = ft_strdup("-9223372036854775808");
	else if (num == LONG_MAX || num == LLONG_MAX)
		int_str = ft_strdup("9223372036854775807");
	else if (num == 32768)
		int_str = ft_strdup("-32768");
	else
	{
		num < 0 ? sign = -1 : 1;
		num < 0 ? pf->s.neg = 1 : 0;
		int_str = ft_dtoa(num);
	}
	handle_precision(pf, &int_str);
	print_digits(pf, int_str);
	free(int_str);
}

void			signed_int_handler(const char *fmt, va_list ap, t_pf_token *pf)
{
	ft_bzero(&pf->s, sizeof(pf->s));
	if (fmt[pf->i] == 'd' || fmt[pf->i] == 'i')
		print_int(ap, pf);
	else if (fmt[pf->i] == 'f')
		print_float(ap, pf);
}
