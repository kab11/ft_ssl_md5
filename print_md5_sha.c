/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_md5_sha.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 16:19:29 by kblack            #+#    #+#             */
/*   Updated: 2019/07/13 17:50:38 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	tranform_to_big_endian(t_ssl *ms)
{
	ms->var[0] = convert_to_big_endian(ms->var[0]);
	ms->var[1] = convert_to_big_endian(ms->var[1]);
	ms->var[2] = convert_to_big_endian(ms->var[2]);
	ms->var[3] = convert_to_big_endian(ms->var[3]);
}

void	print_hash(t_ssl *ms, char *input)
{
	tranform_to_big_endian(ms);
	if (!(ms->flag & (FLAG_Q | FLAG_R | PIPE)))
	{
		(ms->flag & FLAG_S) == 1 ? ft_printf("MD5 (\"%s\") = ", input)
			: ft_printf("MD5 (%s) = ", input);
	}
	ft_printf("%.8x%.8x%.8x%.8x",
		ms->var[0], ms->var[1], ms->var[2], ms->var[3]);
	if (!(ms->flag & (FLAG_Q | PIPE)) && (ms->flag & FLAG_R))
	{
		(ms->flag & FLAG_S) == 1 ? ft_printf(" \"%s\"", input)
			: ft_printf(" %s", input);
	}
	ft_printf("\n");
	(ms->flag & FLAG_S) ? BIT_OFF(ms->flag, FLAG_S) : 0;
}

void	print_sha_hash(t_sha *sh, char *input)
{
	if (!(sh->flag & (FLAG_Q | FLAG_R | PIPE)))
	{
		(sh->flag & FLAG_S) == 1 ? ft_printf("SHA256 (\"%s\") = ", input)
			: ft_printf("SHA256 (%s) = ", input);
	}
	ft_printf("%.8x%.8x%.8x%.8x%.8x%.8x%.8x%.8x", sh->state[0], sh->state[1],
		sh->state[2], sh->state[3], sh->state[4], sh->state[5], sh->state[6],
		sh->state[7]);
	if (!(sh->flag & (FLAG_Q | PIPE)) && (sh->flag & FLAG_R))
	{
		(sh->flag & FLAG_S) == 1 ? ft_printf(" \"%s\"", input)
			: ft_printf(" %s", input);
	}
	ft_printf("\n");
	(sh->flag & FLAG_S) ? BIT_OFF(sh->flag, FLAG_S) : 0;
}
