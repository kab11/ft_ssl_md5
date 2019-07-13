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
	- The message is "padded" so that the length in bits is congruent to 448,
	modulo 512; the message is extended so that its just 64 bits shy of being
	a multiple of 512 bits long
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


/* Rounds constants */
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

int md5_padding(uint8_t *init_msg, size_t init_len, t_ssl *ms)
{
	uint64_t new_len;

	new_len = init_len * 8;
	while (new_len % 512 != 448)
		new_len++;

	new_len /= 8;
	ms->msg = ((uint8_t*)ft_strnew(new_len + 8));
	ft_memcpy((char*)ms->msg, (const char*)init_msg, init_len);
	ms->msg[init_len] = 0x80;
	((uint64_t *)ms->msg)[new_len / 8] = (uint64_t)(init_len * 8);
	ms->msg_len = (uint64_t)(new_len + 8);
	// for (int i = 0; i < 16; i++)
	//  	printf("[%.2d]: %u\n", i, ((uint32_t*)(ms->msg))[i]);
	return (0);
}

void md5_rounds(t_ssl *ms)
{
	unsigned int f = 0;
	unsigned int g = 0;
	unsigned int x = 0;

	while (x < 64)
	{
		if (x <= 15)
		{
			f = F(ms->b, ms->c, ms->d);
			//f = (b & c) | ((~b) & d);
			g = x;
		}
		else if (x >= 16 && x <= 31)
		{
			f = G(ms->b, ms->c, ms->d);
			//f = (d & b) | ((~d) & c);
			g = (5 * x + 1) % 16;
		}
		else if (x >= 32 && x <= 47)
		{
			f = H(ms->b, ms->c, ms->d);
			//f = (b ^ c ^ d);
			g = (3 * x + 5) % 16;
		}
		else
		{
			f = I(ms->b, ms->c, ms->d);
			//f = (c ^ (b | (~d)));
			g = (7 * x) % 16;
		}
	
		// f = f + ms->a + k[x] + ms->msg32[g];
		uint32_t tmp = ms->d;	
		ms->d = ms->c;
		ms->c = ms->b;
		// printf("rotateLeft(%x + %x  + %x + %x, %d)\n", ms->a, f, k[x], ms->msg32[g], s[x]);
		ms->b = ms->b + ROTATE_LEFT((ms->a + f + ms->msg32[g] + k[x]), s[x]);
		ms->a = tmp;
		
		// ft_printf("ROUND %d\t", x);
		// ft_printf("a: %u ", ms->a);
		// ft_printf("b: %u ", ms->b);
		// ft_printf("c: %u ", ms->c);
		// ft_printf("d: %u\n", ms->d);
		x++;
	}
}

void md5_algo(t_ssl *ms)
{
	unsigned int i = 0;
	unsigned int j;
	// printf("msg len = %u\n", ms->msg_len);

	while (i < ms->msg_len)
	{
		ms->a = ms->var[0];
		ms->b = ms->var[1];
		ms->c = ms->var[2];
		ms->d = ms->var[3];
		j = 0;
		ms->msg32 = (uint32_t*)(ms->msg + i);
		md5_rounds(ms);
		ms->var[0] += ms->a;
		ms->var[1] += ms->b;
		ms->var[2] += ms->c;
		ms->var[3] += ms->d;
		i += (64);
	}
	// ft_printf("a => %.8x\n", convert_to_big_endian(ms->var[0]));
	// ft_printf("b => %.8x\n", convert_to_big_endian(ms->var[1]));
	// ft_printf("c => %.8x\n", convert_to_big_endian(ms->var[2]));
	// ft_printf("d => %.8x\n", convert_to_big_endian(ms->var[3]));
}

void	handle_md5(char **av)
{
	int i;
	int fd;
	char *input;
	t_ssl *ms;

	i = 1;
	bzero(&ms, sizeof(ms));
	ms->flag |= turn_on_flags(av);
	input = av[0];
	while(av[i] && av[i][0] == '-')
		av += 1;
	if (!isatty(0))
	{
		// printf("stdin\n");
		read_stdin_and_file(0, ms, av[i]);
	}
	while (av[i])
	{
		pre_processing(ms);
		if (check_dir(av[i]) == 0)
			ft_printf("%s: %s: Is a directory\n", av[0], av[i]);
		else if (ms->flag & FLAG_S)
		{
			// printf("this is s\n");
			// BIT_OFF(ms->flag, FLAG_S);
			md5_padding((uint8_t*)av[i], ft_strlen(av[i]), ms);
			md5_algo(ms);
			print_hash(ms, av[i]);
		}
		else if (check_file(av[i]) == 0)
		{
			// printf("is a file\n");
			if ((fd = open(av[i], O_RDONLY))  -1)
				read_stdin_and_file(fd, ms, av[i]);
		}
		// printf("av = %s\n", av[i]);
		i++;
	}
}
