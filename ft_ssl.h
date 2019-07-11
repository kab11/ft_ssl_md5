/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 16:07:28 by kblack            #+#    #+#             */
/*   Updated: 2019/04/05 14:03:53 by kblack           ###   ########.fr       */
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
// # include <inttypes.h>

/*
** Bit operations 
*/

# define BIT_ON(x, y) x |= y
# define BIT_OFF(x, y) x &= (~y)
# define BIT_FLIP(x, y) x ^= y

/*
** Rotate left in bits
*/

# define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

/*
** Processes Message in 16-word blocks
** Takes input of 32-bit words and produces as output one 32-bit word
*/

# define F(x, y, z) ((x & y) | ((~x) & z))
# define G(x, y, z) ((x & z) | (y & ~z))
# define H(x, y, z) (x ^ y ^ z)
# define I(x, y, z) (y ^ (x | ~z))

/*
** Number of elements in the dispatch table
*/

# define HASH_COUNT 1

/*
** Bit masks
*/

enum e_flag
{
	OPT_P = 1 << 0,
	OPT_Q = 1 << 1,
	OPT_R = 1 << 2,
	OPT_S = 1 << 3	
};

typedef struct s_ssl
{
	int flag;
	int var[4];
	int buf[64 * 2];
	int bytes_read;
	uint8_t total_bytes;
	void *content;
	unsigned int A;
	unsigned int B;
	unsigned int C;
	unsigned int D;
	uint8_t *msg;
}				t_ssl;

typedef void (t_fxnptr)(char**, t_ssl*);

typedef struct s_dispatch
{
	char		*key;
	t_fxnptr	*fxnptr;
}				t_dispatch;

void	handle_md5(char **av, t_ssl *ms);
void	handle_256(char **av, t_ssl *ms);

int		turn_on_flags(char **av, t_ssl *ms);

int	check_file(char *name);
int	check_dir(char *name);
void *ft_calloc(size_t count, size_t size);

int					gnl_return_bytes(const int fd, char **line, t_ssl *s, size_t size);

#endif
