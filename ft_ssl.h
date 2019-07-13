/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 16:07:28 by kblack            #+#    #+#             */
/*   Updated: 2019/07/11 22:44:19 by kblack           ###   ########.fr       */
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

# define ROTATE_LEFT(x, n) ((x << n) | (x >> (32 - n)))

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

enum e_flag
{
	FLAG_P = 1 << 0,
	FLAG_Q = 1 << 1,
	FLAG_R = 1 << 2,
	FLAG_S = 1 << 3,
	PIPE = 1 << 4	
};

typedef struct s_ssl
{
	unsigned int flag;
	unsigned int var[4];
	unsigned int state[8];
	int buf[16];
	unsigned int bytes_read;
	unsigned int total_bytes;
	void *content;
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
	// unsigned int g;
	// unsigned int x;
	uint8_t *msg;
	uint64_t msg_len;
	uint32_t *msg32;
}				t_ssl;

// typedef void (t_fxnptr)(char**, t_ssl*);
typedef void (t_fxnptr)(char**);

typedef struct s_dispatch
{
	char		*key;
	t_fxnptr	*fxnptr;
}				t_dispatch;

void	handle_md5(char **av);
void	handle_256(char **av);

int		turn_on_flags(char **av);

int	check_file(char *name);
int	check_dir(char *name);
unsigned			convert_to_big_endian(unsigned n);
void *ft_calloc(size_t count, size_t size);
void	print_bits(unsigned long octet);
size_t get_msg_length(uint8_t *word);
void read_stdin_and_file(int fd, t_ssl *ms, char *input);

void md5_algo(t_ssl *ms);
int md5_padding(uint8_t *init_msg, size_t init_len, t_ssl *ms);


void print_hash(t_ssl *ms, char* input);

int					gnl_return_bytes(const int fd, char **line, t_ssl *s, size_t size);

#endif
