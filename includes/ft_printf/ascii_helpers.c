/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:45:26 by kblack            #+#    #+#             */
/*   Updated: 2019/03/07 16:45:38 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_ch_width(t_pf_token *pf)
{
	int		i;

	i = 0;
	while (pf->flag.width - i++ > 1)
		pf->out += (pf->flag.zero == 1 ? write(1, "0", 1) : write(1, " ", 1));
}

void		char_arg(va_list ap, t_pf_token *pf, int *ch)
{
	*ch = va_arg(ap, int);
	if (!*ch)
	{
		if (pf->flag.left == 1)
		{
			pf->out += write(1, "\0", 1);
			print_ch_width(pf);
		}
		else
		{
			print_ch_width(pf);
			pf->out += write(1, "\0", 1);
		}
	}
	else if (pf->flag.left == 1)
	{
		pf->out += write(1, ch, 1);
		print_ch_width(pf);
	}
	else
	{
		print_ch_width(pf);
		pf->out += write(1, ch, 1);
	}
}

void		null_str(t_pf_token *pf)
{
	int		len;
	char	*null;

	null = ft_strdup("(null)");
	len = ++pf->flag.prec;
	if (pf->flag.left == 1)
	{
		pf->out += write(1, null, ft_strlen(null));
		while (pf->flag.width > pf->flag.prec && pf->flag.width--)
		{
			pf->out += (pf->flag.zero == 1 ?
				write(1, "0", 1) : write(1, " ", 1));
		}
	}
	else
	{
		while (pf->flag.width > pf->flag.prec && pf->flag.width--)
		{
			pf->out += (pf->flag.zero == 1 ?
				write(1, "0", 1) : write(1, " ", 1));
		}
		pf->out += write(1, null, ft_strlen(null));
	}
	free(null);
}
