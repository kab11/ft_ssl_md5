/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 12:57:52 by kblack            #+#    #+#             */
/*   Updated: 2019/03/07 17:11:32 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double		find_double_size(va_list ap, t_pf_token *pf)
{
	long double	length;

	if (pf->u.ld)
		length = va_arg(ap, long double);
	else
		length = va_arg(ap, double);
	return (length);
}

void			get_float_precision(long double num, t_pf_token *pf)
{
	int			prec;
	long		deci;

	pf->f.whole = ft_ltoa(num);
	num == 0 ? pf->flag.prec-- : 0;
	prec = ft_strlen(pf->f.whole);
	deci = get_decimal(num, pf->flag.prec);
	pf->f.wd = (num == 0 ? ft_strdup("0000000") : ft_ftoa(deci));
	if (pf->flag.prec == 0 && pf->flag.hash == 1)
		pf->f.str = handle_flt_prec(prec, pf->f.wd, prec + pf->flag.prec, pf);
	else if (pf->flag.prec == 0)
		pf->f.str = ft_strdup(pf->f.whole);
	else
		pf->f.str = handle_flt_prec(prec, pf->f.wd, prec + pf->flag.prec, pf);
}

void			print_float_width(t_pf_token *pf)
{
	int			i;
	int			len;

	i = 0;
	len = ft_strlen(pf->f.str + pf->flag.plus + pf->flag.space);
	if (pf->flag.prec >= 0)
	{
		while (pf->flag.width - i++ > len)
			pf->out += pf->flag.zero == 1 ? write(1, "0", 1) : write(1, " ", 1);
		i = 0;
		while ((int)ft_strlen(pf->f.str) < len - i++)
			pf->out += write(1, "0", 1);
	}
	else
		while (pf->flag.width - i++ > len)
			pf->out += pf->flag.zero == 1 ? write(1, "0", 1) : write(1, " ", 1);
}

void			float_handler(long double num, t_pf_token *pf)
{
	get_float_precision(num, pf);
	if (pf->flag.left == 1)
	{
		if (num > 0 && (pf->flag.plus == 1 || pf->flag.space == 1))
			pf->out += (pf->flag.plus == 1 ?
				write(1, "+", 1) : write(1, " ", 1));
		pf->out += write(1, pf->f.str, ft_strlen(pf->f.str));
		print_float_width(pf);
	}
	else
	{
		print_float_width(pf);
		if (num > 0 && (pf->flag.plus == 1 ||
			pf->flag.space == 1))
			pf->out += (pf->flag.plus == 1 ?
				write(1, "+", 1) : write(1, " ", 1));
		pf->out += write(1, pf->f.str, ft_strlen(pf->f.str));
	}
	free(pf->f.str);
	free(pf->f.wd);
	free(pf->f.whole);
}

void			print_float(va_list ap, t_pf_token *pf)
{
	long double	num;

	ft_bzero(&pf->f, sizeof(pf->f));
	num = find_double_size(ap, pf);
	if (NAN(num))
		print_nan(pf);
	else if (INF(num))
		print_inf(pf);
	else
		float_handler(num, pf);
}
