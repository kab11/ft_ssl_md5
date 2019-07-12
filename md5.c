/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 22:11:18 by kblack            #+#    #+#             */
/*   Updated: 2019/07/11 22:49:12 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
	uint8_t (1 byte) == unsigned char [0-255] [0x00-0xFF]
	uint16_t (2bytes) == unsigned short [0-65535] [0x0000-0xFFFF]
	uint32_t (32 bytes) == unsigned int [0-4294967295] [0x00000000-0xFFFFFFFF]
	uint64_t (64 bytes) == unsigned long long [0-184467440733709551615] [0x0000000000000000-0xFFFFFFFFFFFFFFFF]
*/

/*
	size_t: is guaranteed to be big enough to contain the size of the biggest object
			the host system can handle (compiler dependent)
	- its never negative 
	- refers to the max blocks that can be allocated which is guaranteed to be non-neg
*/


unsigned int s[64] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};


// /*  */
unsigned int k[64] = {	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

void pre_processing(t_ssl *ms)
{
	/* Initialize variables */
	ms->var[0] = 0x67452301;
	ms->var[1] = 0xefcdab89;
	ms->var[2] = 0x98badcfe;
	ms->var[3] = 0x10325476;
}

unsigned			convert_to_big_endian(unsigned n)
{
	return ((n << 24) | ((n << 8) & 0x00ff0000) | ((n >> 8) & 0x0000ff00) | (n >> 24));
}

/*
	- The message is "padded" so that the length in bits is congruent to 448,
	modulo 512; the message is extended so that its just 64 bits shy of being
	a multiple of 512 bits long
*/

#include <math.h>

void	print_bits(unsigned long octet)
{
	size_t				i;
	unsigned char	c;

	i = pow(2, 63);
	while (i > 0)
	{
		if (octet < i)
		{
			c = '0';
			write(1, &c, 1);
			i /= 2;
		}
		else
		{
			c = '1';
			write(1, &c, 1);
			octet = octet - i;
			i /= 2;
		}
	}
	// printf("i = %d\n", i);
}

/*
** the newline character is equivalent to the ASCII linefeed character hex0A
*/

size_t get_msg_length(uint8_t *word)
{
	size_t i;

	i = 0;
	while (word[i] || (word[i] >= 8 && word[i] <= 14))
		i++;
	return (i);
}

int md5_padding(uint8_t *init_msg, size_t init_len, t_ssl *ms)
{
	size_t new_len;

	new_len = init_len * 8;
	while (new_len % 512 != 448)
		new_len++;
	new_len /= 8;
	printf("new_len = %zu\n", new_len);
	if (!(ms->msg = (unsigned char*)malloc(new_len + 8)))
		return (-1);
	ft_memcpy(ms->msg, init_msg, init_len);
	ms->msg[init_len] = 0x80;
	// uint32_t bits_len = 8 * init_len;
	((uint64_t *)ms->msg)[7] = (init_len * 8);
	ms->msg_len = new_len + 8;
	// ft_memcpy(ms->msg + new_len, &bits_len, 4);
	for (int i = 0; i < 16; i++)
	 	printf("[%.2d]: %u\n", i, ((uint32_t*)(ms->msg))[i]);

	return (0);
}

void md5_rounds(t_ssl *ms)
{
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
	uint32_t msg32[16];
	int g;
	unsigned long f;

	unsigned int i = 0;
	unsigned int j;
	unsigned int x;
	printf("msg len = %u\n", ms->msg_len);

	while (i < (ms->msg_len / 64))
	{
		a = ms->var[0];
		b = ms->var[1];
		c = ms->var[2];
		d = ms->var[3];

		printf("a: %u\n", (int)a);
		printf("b: %u\n", (int)b);
		printf("c: %u\n", (int)c);
		printf("d: %u\n", (int)d);
		j = 0;
		while (j < 16)
		{
			msg32[j] = ((uint32_t*)ms->msg)[j];
			j++;
		}
		x = 0;
		while (x < 64)
		{
			if (x < 16)
			{
				f = F(b, c, d);
				//f = (b & c) | ((~b) & d);
				g = x;
			}
			else if (x < 32)
			{
				f = G(b, c, d);
				//f = (d & b) | ((~d) & c);
				g = (5 * x + 1) % 16;
			}
			else if (x < 48)
			{
				f = H(b, c, d);
				//f = (b ^ c ^ d);
				g = (3 * x + 5) % 16;
			}
			else
			{
				f = I(b, c, d);
				//f = (c ^ (b | (~d)));
				g = (7 * x) % 16;
			}
		
			f = f + a + k[x] + ((uint32_t*)ms->msg)[g];

			unsigned int tmp = d;	
			d = c;
			c = b;
			b = b + ROTATE_LEFT(f, s[x]);
			a = tmp;
			
			ft_printf("ROUND %d\t", x);
			ft_printf("a: %u ", a);
			ft_printf("b: %u ", b);
			ft_printf("c: %u ", c);
			ft_printf("d: %u\n", d);
			x++;
		}
		ms->var[0] += a;
		ms->var[1] += b;
		ms->var[2] += c;
		ms->var[3] += d;

		i++;

	}
	printf("a: %u\n", a);
	printf("b: %u\n", b);
	printf("c: %u\n", c);
	printf("d: %u\n", d);
}

void read_in_file(int fd, t_ssl *ms, char *file)
{
	int n;

	n = 0;
	while ((ms->bytes_read = gnl_return_bytes(fd, &file, ms, 64)) > 0)
	{
		printf("bytes_read = %d\n", ms->bytes_read);
		ms->total_bytes += ms->bytes_read;
		free(file);
	}
	printf("total_bytes = %d\n", ms->total_bytes);
	printf("content = %s", (char*)ms->content);
}

void	handle_md5(char **av, t_ssl *ms)
{
	int i;
	size_t init_len;
	char **args;

	i = 0;
	args = av + 1;
	printf("arg = %s\n", args[i]);
	init_len = ft_strlen(args[i]);
	printf("ENTERING MD5\n");
	if (check_dir(args[i]) == 0)
		ft_printf("%s: %s: Is a directory\n", av[0], args[i]);
	else if (check_file(args[i]) == 0)
	{
		printf("is a file\n");
		int fd;
		unsigned long f = 0;
		unsigned long a = ms->var[0];
		unsigned long b = ms->var[1];
		unsigned long c = ms->var[2];
		unsigned long d = ms->var[3];
		int g = 0;
		unsigned char *msg;
		int new_len;

		new_len = 0;
		if ((fd = open(args[i], O_RDONLY)) > -1)
		{
			printf("file \'%s\': is valid\n", args[i]);
			read_in_file(fd, ms, args[i]);
			// md5_update((uint8_t*)args[i], init_len);
			pre_processing(ms);
			// printf("a = %#010x\t b = %#010x\t c = %#010x\t d = %#010x\n", ms->var[0], ms->var[1], ms->var[2], ms->var[3]);
			
			new_len = ms->total_bytes + 1;
			while (new_len % 64 != 56)
				new_len++;
			msg = (unsigned char*)malloc(sizeof(new_len + 64));
			ft_bzero(msg, new_len + 64);
			ft_strcpy((char*)msg, args[i]);
			printf("msg = %s\n", msg);
			int i = -1;

			while (++i < 64)
			{
				if (i < 16)
				{
					f = F(ms->var[1], ms->var[2], ms->var[3]);
					g = i;
				}
				else if(i < 32)
				{
					f = G(ms->var[1], ms->var[2], ms->var[3]);
					g = (i * 5) % 16;
				}
				else if (i < 48)
				{
					f = H(ms->var[1], ms->var[2], ms->var[3]);
					g = (i * 3) % 16;
				}
				else
				{
					f = I(ms->var[1], ms->var[2], ms->var[3]);
					g = (i * 5) % 16;
				}
				f = f + a + k[i] + ms->buf[g];
				a = d;
				d = c;
				c = b;
				b = b + ROTATE_LEFT(f, s[i]);
			}
			ms->var[0] += a;
			ms->var[1] += b;
			ms->var[2] += c;
			ms->var[3] += d;
		}
		printf("a: %x\n", (int)a);
		printf("b: %x\n", (int)b);
		printf("c: %x\n", (int)c);
		printf("d: %x\n", (int)d);
		close(fd);
	}
	else if (isatty(fileno(stdin)))
	{
		printf("stdin\n");
		pre_processing(ms);
		md5_padding((uint8_t*)args[i], init_len, ms);
		md5_rounds(ms);
	}
	else
	{
		int i = 0;
    	char pipe[65536];
   	 	while(-1 != (pipe[i++] = getchar()));
   	 	fprintf(stdout, "piped content: >>%c<<\n", pipe[i - 1]);
	}
}
