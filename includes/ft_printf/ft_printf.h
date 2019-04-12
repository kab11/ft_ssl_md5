/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 22:13:21 by kblack            #+#    #+#             */
/*   Updated: 2019/03/07 17:05:47 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include "libft.h"
# include <stdint.h>
# include <float.h>
# include <limits.h>

# define FLAGS " .#+-0123456789hlLf"
# define HEX "0123456789abcdef"
# define HEX_UPPER "0123456789ABCDEF"
# define OCTAL "01234567"

# define ABS(x) (x > 0 ? x : -x)
# define NAN(x) (x != x) ? 1 : 0
# define INF(x) (x * 2 == x && x != 0) ? 1 : 0

typedef struct		s_pf_float_tokens
{
	int				sign;
	char			*whole;
	char			*wd;
	char			*str;
}					t_pf_f;

typedef struct		s_pf_signed_tokens
{
	char			sign;
	char			neg;
	int				num;
}					t_pf_s;

typedef struct		s_pf_unsign_tokens
{
	unsigned int	x: 1;
	unsigned int	xx: 1;
	unsigned int	p: 1;
	unsigned int	h: 1;
	unsigned int	hh: 1;
	unsigned int	l: 1;
	unsigned int	ll: 1;
	unsigned int	ld: 1;
}					t_pf_u;

typedef struct		s_pf_flag_tokens
{
	unsigned int	hash: 1;
	unsigned int	left: 1;
	unsigned int	plus: 1;
	unsigned int	space: 1;
	unsigned int	zero: 1;
	unsigned int	dot: 1;
	int				width;
	int				prec;
}					t_pf_flags;

typedef struct		s_pf_main_tokens
{
	int				i;
	int				out;
	char			ctype;
	t_pf_flags		flag;
	t_pf_u			u;
	t_pf_s			s;
	t_pf_f			f;
}					t_pf_token;

int					ft_printf(const char *fmt, ...);

void				ascii_handler(const char *fmt, va_list ap, t_pf_token *pf);
void				char_arg(va_list ap, t_pf_token *pf, int *ch);
void				get_flags(const char *fmt, t_pf_token *pf);
long				get_decimal(long double num, int prec);
void				get_type(const char *fmt, va_list ap, t_pf_token *pf);
char				*handle_flt_prec(int dot, char *str,
						int len, t_pf_token *pf);
void				handle_precision(t_pf_token *pf, char **int_str);
void				null_str(t_pf_token *pf);
void				print_conversion(const char *fmt,
						va_list ap, t_pf_token *pf);
void				print_digits(t_pf_token *pf,
						char *int_str);
void				print_float(va_list ap, t_pf_token *pf);
void				print_hex_digits(t_pf_token *pf, char *int_str);
void				print_inf(t_pf_token *pf);
void				print_nan(t_pf_token *pf);
void				signed_int_handler(const char *fmt,
						va_list ap, t_pf_token *pf);
void				unsigned_int_handler(const char *fmt,
						va_list ap, t_pf_token *pf);

#endif
