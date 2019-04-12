/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_digits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 23:16:09 by kblack            #+#    #+#             */
/*   Updated: 2019/03/07 17:01:51 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_width(t_pf_token *pf, char *int_str)
{
	int	len;
	int	i;

	pf->flag.width -= (pf->flag.space + (pf->s.neg || pf->flag.plus));
	len = (int)ft_strlen(int_str) > pf->flag.prec ?
		ft_strlen(int_str) : pf->flag.prec;
	i = -1;
	if (pf->flag.prec > 0)
	{
		while (pf->flag.width - ++i > len)
			pf->out += write(1, " ", 1);
		i = 0;
		while ((int)ft_strlen(int_str) < len - i++)
			pf->out += write(1, "0", 1);
	}
	else
	{
		while (pf->flag.width - ++i > len)
			pf->out += (pf->flag.zero == 1) ?
				write(1, "0", 1) : write(1, " ", 1);
	}
}

void	handle_sign(t_pf_token *pf)
{
	if (pf->s.num >= 0 && (pf->flag.plus == 1 || pf->flag.space == 1))
		pf->out += (pf->flag.plus == 1 ? write(1, "+", 1) : write(1, " ", 1));
	else if (pf->s.neg == 1)
		pf->out += write(1, "-", 1);
}

void	print_digits(t_pf_token *pf, char *int_str)
{
	if (pf->flag.zero == 1)
	{
		handle_sign(pf);
		print_width(pf, int_str);
		pf->out += write(1, int_str, ft_strlen(int_str));
	}
	else if (pf->flag.left == 1)
	{
		handle_sign(pf);
		pf->out += write(1, int_str, ft_strlen(int_str));
		print_width(pf, int_str);
	}
	else
	{
		print_width(pf, int_str);
		handle_sign(pf);
		if (int_str[0] == '\0' && pf->flag.dot == 0)
			pf->out += write(1, "0", 1);
		else
			pf->out += write(1, int_str, ft_strlen(int_str));
	}
}
