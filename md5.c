/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 22:11:18 by kblack            #+#    #+#             */
/*   Updated: 2019/06/02 05:11:16 by kblack           ###   ########.fr       */
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

// static unsigned char p[16] = {	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

unsigned int r[64] =  {	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
						5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
						4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
						6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};


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
						0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

void pre_processing(t_ssl *ms)
{
	/* Initialize variables */
	ms->var[0] = 0x67452301;
	ms->var[1] = 0xefcdab89;
	ms->var[2] = 0x98badcfe;
	ms->var[3] = 0x10325476;
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

	new_len = 0;
	new_len = init_len * 8;
	while (new_len % 512 != 448)
		new_len++;
	if (!(ms->msg = ft_calloc(new_len + 64, 1)))
		return (-1);
	ft_memcpy(ms->msg, init_msg, init_len);
	ms->msg[init_len] = 0x80;
	((uint64_t *)ms->msg)[7] = (uint8_t)(init_len * 8);
	// for (int i = 0; i < 8; i++)
	// 	printf("[%.2d]: %llu\n", i, ((uint64_t*)ms->msg)[i]);

	return (0);
}

void md5_rounds(t_ssl *ms)
{
	unsigned int a = ms->var[0];
	unsigned int b = ms->var[1];
	unsigned int c = ms->var[2];
	unsigned int d = ms->var[3];
	int g;
	unsigned long f;

	int t = -1;	 
	int i;
	while (++t < 1)
	{
		i = -1;
		a = ms->var[0];
		b = ms->var[1];
		c = ms->var[2];
		d = ms->var[3];

		while (++i < 64)
		{
			if (i >= 0 && i <= 15)
			{
				f = F(b, c, d);
				g = i;
			}
			else if(i >= 16 && i <= 31)
			{
				f = G(b, c, d);
				g = ((i * 5) + 1) % 16;
			}
			else if (i >= 32 && i <= 47)
			{
				f = H(b, c, d);
				g = ((i * 3) + 5) % 16;
			}
			else if (i >= 48 && i <= 63)
			{
				f = I(b, c, d);
				g = (i * 7) % 16;
			}
			f = f + a + k[i] + ((uint32_t*)ms->msg)[g];
			a = d;
			d = c;
			c = b;
			b += ROTATE_LEFT(f, r[i]);
			printf("ROUND %d\n", i);
			printf("a: %u\n", ms->var[0]);
			printf("b: %u\n", ms->var[1]);
			printf("c: %u\n", ms->var[2]);
			printf("d: %u\n", ms->var[3]);
		}
		ms->var[0] += a;
		ms->var[1] += b;
		ms->var[2] += c;
		ms->var[3] += d;
	}
	printf("a: %x\n", ms->var[0]);
	printf("b: %x\n", ms->var[1]);
	printf("c: %x\n", ms->var[2]);
	printf("d: %x\n", ms->var[3]);
}

void read_in_file(int fd, t_ssl *ms, char *file)
{
	// char *tmp;
	// char *str;
	// str = NULL;
	// while ((ms->bytes_read = read(fd, ms->buf, 64)) > 0)
	// {
	// 	printf("%d", get_next_line(fd, file));
	// 	ms->total_bytes += ms->bytes_read;
	// 	printf("total = %d\n", ms->bytes_read);
	// 	printf("total = %d\n", ms->total_bytes);
	// 	tmp = str;
	// 	str = ft_strjoin(str, (const char*)ms->buf);
	// 	// printf("str =>\t %s\n", str);
	// 	free(tmp);
	// }
	int n;

	n = 0;
	while ((ms->bytes_read = gnl_return_bytes(fd, &file, ms, 64)) > 0)
	{
		printf("bytes_read = %d\n", ms->bytes_read);
		ms->total_bytes += ms->bytes_read;
		// ft_putendl(file);
		free(file);
	}
	printf("total_bytes = %d\n", ms->total_bytes);
	printf("content = %s", (char*)ms->content);
}

void	handle_md5(char **av, t_ssl *ms)
{
	(void)ms;
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
		unsigned long f;
		unsigned long a = ms->var[0];
		unsigned long b = ms->var[1];
		unsigned long c = ms->var[2];
		unsigned long d = ms->var[3];
		int g;
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
			msg = (unsigned char *)malloc(sizeof(new_len + 64));
			ft_bzero(msg, new_len + 64);
			ft_strcpy((char*)msg, args[i]);
			printf("msg = %s\n", msg);

			int t = -1;
			while (++t < ms->total_bytes)
			{
				a = ms->var[0];
				b = ms->var[1];
				c = ms->var[2];
				d = ms->var[3];

				for (int i = 0; i < 64; i++)
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
					f = f + ms->var[0] + k[i] + ms->buf[g];
					ms->var[0] = ms->var[3];
					ms->var[3] = ms->var[2];
					ms->var[2] = ms->var[1];
					ms->var[1] += ROTATE_LEFT(f, r[i]);
				}
				ms->var[0] += a;
				ms->var[1] += b;
				ms->var[2] += c;
				ms->var[3] += d;
			}
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
		md5_padding((uint8_t*)args[i], init_len, ms);
		pre_processing(ms);
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
