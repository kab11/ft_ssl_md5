/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 22:11:31 by kblack            #+#    #+#             */
/*   Updated: 2019/04/05 22:11:37 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/* Rounds Constants */
unsigned int k[64] = {	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
						0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
						0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
						0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
						0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
						0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
						0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
						0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

void sha_pre_processing(t_ssl *sh)
{
	/* Initialize variables */
	sh->state[0]= 0x6a09e667;
	sh->state[1]= 0xbb67ae85;
	sh->state[2]= 0x3c6ef372;
	sh->state[3]= 0xa54ff53a;
	sh->state[4]= 0x510e527f;
	sh->state[5]= 0x9b05688c;
	sh->state[6]= 0x1f83d9ab;
	sh->state[7]= 0x5be0cd19;
}

int sha_padding(uint8_t *init_msg, size_t init_len, t_ssl *sh)
{
	uint64_t new_len;

	new_len = init_len * 8;
	while (new_len % 512 != 448)
		new_len++;

	new_len /= 8;
	sh->msg = ((uint8_t*)ft_strnew(new_len + 8));
	ft_memcpy((char*)sh->msg, (const char*)init_msg, init_len);
	sh->msg[init_len] = 0x80;
	((uint64_t *)sh->msg)[new_len / 8] = (uint64_t)(init_len * 8);
	sh->msg_len = (uint64_t)(new_len + 8);
	for (int i = 0; i < 16; i++)
	 	printf("[%.2d]: %u\n", i, ((uint32_t*)(sh->msg))[i]);
	return (0);
}

void	handle_256(char **av)
{
	int i;
	// int fd;
	char *input;
	t_ssl *sh;

	bzero(&sh, sizeof(sh));
	sh->flag |= turn_on_flags(av);
	printf("In SHA256\n");
	i = 1;
	input = av[0];
	while(av[i] && av[i][0] == '-')
		av += 1;
	if (!isatty(0))
	{
		printf("stdin\n");
		// read_stdin_and_file(0, sh, av[i]);
	}
	while (av[i])
	{
		sha_pre_processing(sh);
		if (check_dir(av[i]) == 0)
			ft_printf("%s: %s: Is a directory\n", av[0], av[i]);
		else if (sh->flag & FLAG_S)
		{
			printf("this is s\n");
			// BIT_OFF(sh->flag, FLAG_S);
			sha_padding((uint8_t*)av[i], ft_strlen(av[i]), sh);
			// sha_algo(sh);
			// print_sha_hash(sh, av[i]);
		}
		else if (check_file(av[i]) == 0)
		{
			printf("is a file\n");
			// if ((fd = open(av[i], O_RDONLY))  -1)
				// read_stdin_and_file(fd, sh, av[i]);
		}
		// printf("av = %s\n", av[i]);
		i++;
	}
}