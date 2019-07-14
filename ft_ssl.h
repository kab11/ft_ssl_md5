/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 16:07:28 by kblack            #+#    #+#             */
/*   Updated: 2019/07/13 17:33:07 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include "libft.h"
# include "ft_printf.h"

/*
** Bit operations
*/

# define BIT_ON(x, y) x |= y
# define BIT_OFF(x, y) x &= (~y)
# define BIT_FLIP(x, y) x ^= y

/*
** Rotate bits
*/

# define ROTATE_LEFT(x, n) ((x << n) | (x >> (32 - n)))
# define ROT_RIGHT(x, n) ((x >> n) | (x << (32 - n)))


/*
** Processes Message in 16-word blocks
** Takes input of 32-bit words and produces as output one 32-bit word
*/

# define F(b, c, d) ((b & c) | ((~b) & d))
# define G(b, c, d) ((d & b) | ((~d) & c))
# define H(b, c, d) (b ^ c ^ d)
# define I(b, c, d) (c ^ (b | (~d)))

/*
** Number of elements in the dispatch table
*/

# define HASH_COUNT 2

/*
** Bit masks
*/

enum			e_flag
{
	FLAG_P = 1 << 0,
	FLAG_Q = 1 << 1,
	FLAG_R = 1 << 2,
	FLAG_S = 1 << 3,
	PIPE = 1 << 4
};

typedef struct		s_ssl
{
	unsigned int	flag;
	unsigned int	var[4];
	int				buf[16];
	unsigned int	bytes_read;
	unsigned int	total_bytes;
	void			*content;
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint8_t			*msg;
	uint64_t		msg_len;
	uint32_t		*msg32;
	unsigned int	f;
	unsigned int	g;
	unsigned int	x;
	uint32_t		tmp;
}					t_ssl;

typedef struct		s_sha
{
	unsigned int	flag;
	unsigned int	state[8];
	int				buf[16];
	unsigned int	bytes_read;
	unsigned int	total_bytes;
	void			*content;
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint32_t		e;
	uint32_t		f;
	uint32_t		g;
	uint32_t		h;
	uint32_t		s0;
	uint32_t		s1;
	uint32_t		ch;
	uint32_t		temp1;
	uint32_t		temp2;
	uint32_t		maj;
	uint32_t		m[64];
	uint8_t			*msg;
	uint64_t		msg_len;
	uint32_t		*msg32;
}					t_sha;

typedef void		(t_fxnptr)(char**, int);

typedef struct		s_dispatch
{
	char			*key;
	t_fxnptr		*fxnptr;
}					t_dispatch;

void				handle_md5(char **av, int flag);
void				handle_256(char **av, int flag);
int					turn_on_flags(char **av);
int					check_file(char *name);
int					check_dir(char *name);
unsigned			convert_to_big_endian(unsigned n);
void				read_stdin_and_file(int fd, t_ssl *ms, char *input);
void				md5_algo(t_ssl *ms);
void				md5_padding(uint8_t *init_msg, size_t init_len, t_ssl *ms);
void				print_hash(t_ssl *ms, char *input);
void				pre_processing(t_ssl *ms);

/*
** SHA Utilities
*/
void				read_sha_stdin(int fd, t_sha *sh, char *input);
int					sha_padding(uint8_t *init_msg, size_t init_len, t_sha *sh);
void				sha_algo(t_sha *sh);
void				print_sha_hash(t_sha *sh, char *input);
void				sha_pre_processing(t_sha *sh);

#endif
