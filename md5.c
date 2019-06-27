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

// unsigned int r[32] =  {	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
// 						5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
// 						4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
// 						6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};


// /*  */
// unsigned int k[32] = {	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
// 						0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
// 						0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
// 						0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
// 						0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
// 						0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
// 						0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
// 						0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
// 						0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
// 						0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
// 						0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
// 						0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
// 						0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
// 						0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
// 						0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
// 						0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

// void pre_processing(t_ssl *ms)
// {
// 	/* Initialize variables */
// 	ms->var[0] = 0x67452301;
// 	ms->var[1] = 0xefcdab89;
// 	ms->var[2] = 0x98badcfe;
// 	ms->var[3] = 0x10325476;
// }

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

int md5_update(uint8_t *init_msg, size_t init_len)
{
	size_t new_len;

	uint8_t *msg = NULL;

	printf("int = %s\n", init_msg);
	printf("len = %zu\n", ft_strlen((char*)init_msg));
	// for(size_t i = 0; i < init_len; i++)
	// {
	// 	print_bits(*init_msg);
	// 	init_msg++;
	// 	printf("\n");
	// }
	new_len = init_len * 8; /* start with 3 bytes == 24 bits */
	while (new_len % 512 != 448)
		new_len++;
	// printf("new after = %zu\n", new_len);
	if (!(msg = ft_calloc(new_len + 64, 1)))
		return (-1);
	ft_memcpy(msg, init_msg, init_len);
	msg[init_len] = 10;
	// for(size_t i = 0; i < new_len; i++)
	// {
	// 	print_bits(*msg);
	// 	msg++;
	// 	printf("\n");
	// }
	
	/* Append a 64-bit representation of init_msg */
	uint32_t app_msg = init_len * 8;	
	ft_memcpy(msg + new_len, &app_msg, 4);

	/* print the bits */
	// for(size_t i = 0; i < new_len; i++)
	// 	print_bits(init_msg[i]);
	// printf("\n");
	for(size_t i = 0; i < new_len; i++)
	{
		print_bits(msg[i]);
		printf("\n");
	}
	printf("new = %zu\n", init_len); 
	print_bits(init_len);
	return (0);
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
		printf("is a file");
	else if (isatty(fileno(stdin)))
	{
		printf("stdin\n");
		md5_update((uint8_t*)args[i], init_len);
	}
	else
	{
		int i = 0;
    	char pipe[65536];
   	 	while(-1 != (pipe[i++] = getchar()));
   	 	fprintf(stdout, "piped content: >>%c<<\n", pipe[i - 1]);
	}
	// pre_processing(ms);
}
