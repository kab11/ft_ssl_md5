/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_int_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 17:30:06 by kblack            #+#    #+#             */
/*   Updated: 2019/03/07 15:53:24 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

uintmax_t		find_ulen_size(va_list ap, t_pf_token *pf)
{
	uintmax_t	length;

	if (pf->u.ll || pf->ctype == 'p')
		length = (uintmax_t)va_arg(ap, unsigned long long);
	else if (pf->u.l)
		length = (uintmax_t)va_arg(ap, unsigned long);
	else if (pf->u.hh)
		length = (uintmax_t)(unsigned char)va_arg(ap, unsigned int);
	else if (pf->u.h)
		length = (uintmax_t)(unsigned short)va_arg(ap, unsigned int);
	else
		length = (uintmax_t)va_arg(ap, unsigned int);
	return (length);
}

void			pf_base8(va_list ap, t_pf_token *pf)
{
	uintmax_t	num;
	uintmax_t	tmp;
	char		*int_str;
	int			i;

	num = find_ulen_size(ap, pf);
	tmp = num;
	i = 1;
	while (tmp > 8)
	{
		tmp /= 8;
		i++;
	}
	int_str = (char *)malloc(sizeof(char) * (i + 1));
	int_str[i] = '\0';
	i--;
	while (i >= 0)
	{
		int_str[i] = OCTAL[num & 0x7];
		num >>= 3;
		i--;
	}
	handle_precision(pf, &int_str);
	print_hex_digits(pf, int_str);
	free(int_str);
}

void			pf_base10(va_list ap, t_pf_token *pf)
{
	uintmax_t	num;
	uintmax_t	tmp;
	char		*int_str;
	int			i;

	num = find_ulen_size(ap, pf);
	tmp = num;
	i = 1;
	while (tmp > 9)
	{
		tmp /= 10;
		i++;
	}
	int_str = (char *)malloc(sizeof(char) * (i + 1));
	int_str[i--] = '\0';
	while (i >= 0)
	{
		int_str[i] = num % 10 + '0';
		num /= 10;
		i--;
	}
	handle_precision(pf, &int_str);
	print_hex_digits(pf, int_str);
	free(int_str);
}

void			pf_base16(va_list ap, t_pf_token *pf)
{
	uintmax_t	num;
	uintmax_t	tmp;
	char		*int_str;
	int			i;

	num = find_ulen_size(ap, pf);
	tmp = num;
	i = (num == 0 ? 1 : 0);
	while (tmp > 0 && ++i)
		tmp >>= 4;
	int_str = (char *)malloc(sizeof(char) * (i + 1));
	int_str[i] = '\0';
	i--;
	while (i >= 0)
	{
		if (pf->u.x || pf->u.p)
			int_str[i] = HEX[num & 0xF];
		else
			int_str[i] = HEX_UPPER[num & 0xF];
		num >>= 4;
		i--;
	}
	handle_precision(pf, &int_str);
	print_hex_digits(pf, int_str);
	free(int_str);
}

void			unsigned_int_handler(const char *fmt,
	va_list ap, t_pf_token *pf)
{
	if (fmt[pf->i] == 'o')
		pf_base8(ap, pf);
	else if (fmt[pf->i] == 'u')
		pf_base10(ap, pf);
	else if (fmt[pf->i] == 'x')
	{
		pf->u.x = 1;
		pf_base16(ap, pf);
	}
	else if (fmt[pf->i] == 'X')
	{
		pf->u.xx = 1;
		pf_base16(ap, pf);
	}
	else if (fmt[pf->i] == 'p')
	{
		pf->u.p = 1;
		pf_base16(ap, pf);
	}
}
