/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 22:11:31 by kblack            #+#    #+#             */
/*   Updated: 2019/07/13 18:15:23 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int g_w[64] = {	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
	0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa,
	0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138,
	0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624,
	0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f,
	0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

int					sha_padding(uint8_t *init_msg, uint64_t init_len, t_sha *sh)
{
	int			i;
	uint64_t	new_len;

	i = -1;
	new_len = init_len * 8;
	while (new_len % 512 != 448)
		new_len++;
	new_len /= 8;
	sh->msg = ((uint8_t*)ft_strnew(new_len + 8));
	ft_memcpy((char*)sh->msg, (const char*)init_msg, init_len);
	sh->msg[init_len] = 0x80;
	init_len *= 8;
	while (++i < 8)
		sh->msg[new_len + i] = ((uint8_t*)&init_len)[7 - i];
	sh->msg_len = new_len + 8;
	return (0);
}

void				add_to_hash(t_sha *sh)
{
	sh->state[0] += sh->a;
	sh->state[1] += sh->b;
	sh->state[2] += sh->c;
	sh->state[3] += sh->d;
	sh->state[4] += sh->e;
	sh->state[5] += sh->f;
	sh->state[6] += sh->g;
	sh->state[7] += sh->h;
}

void				main_loop(t_sha *sh)
{
	// printf("sha256 main loop\n");
	int				i;

	i = -1;
	while (++i < 64)
	{
		// printf("ROUND[%i]: %.8x\t%.8x\t%.8x\t%.8x\t%.8x\t%.8x\t%.8x\t%.8x\n", i, sh->a, sh->b, sh->c, sh->d, sh->e, sh->f, sh->g, sh->h);
		sh->s1 = ROT_RIGHT(sh->e, 6) ^ ROT_RIGHT(sh->e, 11) ^ ROT_RIGHT(sh->e, 25);
		sh->ch = (sh->e & sh->f) ^ ((~sh->e) & sh->g);
		sh->temp1 = sh->h + sh->s1 + sh->ch + g_w[i] + sh->m[i];
		sh->s0 = ROT_RIGHT(sh->a, 2) ^ ROT_RIGHT(sh->a, 13) ^ ROT_RIGHT(sh->a, 22);
		sh->maj = (sh->a & sh->b) ^ (sh->a & sh->c) ^ (sh->b & sh->c);
		sh->temp2 = sh->s0 + sh->maj;
		sh->h = sh->g;
		sh->g = sh->f;
		sh->f = sh->e;
		sh->e = sh->d + sh->temp1;
		sh->d = sh->c;
		sh->c = sh->b;
		sh->b = sh->a;
		sh->a = sh->temp1 + sh->temp2;
	}
}

void				sha_setup(t_sha *sh)
{
	unsigned int	j;

	j = -1;
	ft_bzero(sh->m, sizeof(uint32_t) * 64);
	while (++j < 16)
		sh->m[j] = convert_to_big_endian(((uint32_t *)sh->msg)[j]);
	j = 15;
	while (++j < 64)
	{
		sh->s0 = ROT_RIGHT(sh->m[j - 15], 7) ^ ROT_RIGHT(sh->m[j - 15], 18) ^ (sh->m[j - 15] >> 3);
		sh->s1 = ROT_RIGHT(sh->m[j - 2], 17) ^ ROT_RIGHT(sh->m[j - 2], 19) ^ (sh->m[j - 2] >> 10);
		sh->m[j] = sh->m[j - 16] + sh->s0 + sh->m[j - 7] + sh->s1;
	}
	sh->a = sh->state[0];
	sh->b = sh->state[1];
	sh->c = sh->state[2];
	sh->d = sh->state[3];
	sh->e = sh->state[4];
	sh->f = sh->state[5];
	sh->g = sh->state[6];
	sh->h = sh->state[7];
}

void				sha_algo(t_sha *sh)
{
	unsigned int i;
	uint8_t			*name;

	i = 0;
	name = sh->msg;
	printf("sha msg length = %llu\n", sh->msg_len);
	sha_pre_processing(sh);
	while (i < sh->msg_len)
	{
		sha_setup(sh);
		main_loop(sh);
		add_to_hash(sh);
		sh->msg += 64;
		i += 64;
	}
	free(name);
}

void				handle_256(char **av, int flag)
{
	// printf("enter");
	int				i;
	int				fd;
	t_sha			sh;

	i = 1;
	ft_bzero(&sh, sizeof(sh));
	while (av[i] && av[i][0] == '-')
		i++;
	if (!isatty(0))
		read_sha_stdin(0, &sh, av[i]);
	while (av[i])
	{
		if (check_dir(av[i]) == 0)
			ft_printf("%s: %s: Is a directory\n", av[0], av[i]);
		else if (flag & FLAG_S)
		{
			sha_padding((uint8_t*)av[i], ft_strlen(av[i]), &sh);
			sha_algo(&sh);
			print_sha_hash(&sh, av[i]);
		}
		else if (check_file(av[i]) == 0)
			if ((fd = open(av[i], O_RDONLY)) > -1)
				read_sha_stdin(fd, &sh, av[i]);
		i++;
	}
}
