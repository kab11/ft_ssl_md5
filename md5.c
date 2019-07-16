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

unsigned int g_s[64] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

unsigned int g_k[64] = {	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
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

void				md5_padding(uint8_t *init_msg, uint64_t init_len, t_ssl *ms)
{
	uint64_t		new_len;

	new_len = init_len * 8;
	while (new_len % 512 != 448)
		new_len++;
	new_len /= 8;
	ms->msg = ((uint8_t*)ft_strnew(new_len + 8));
	ft_memcpy((char*)ms->msg, (const char*)init_msg, init_len);
	ms->msg[init_len] = 0x80;
	((uint64_t *)ms->msg)[new_len / 8] = (uint64_t)(init_len * 8);
	ms->msg_len = (uint64_t)(new_len + 8);
}

void				adjust_working_var(t_ssl *ms)
{
	ms->tmp = ms->d;
	ms->d = ms->c;
	ms->c = ms->b;
	ms->b = ms->b + ROTATE_LEFT((ms->a + ms->f +
		ms->msg32[ms->g] + g_k[ms->x]), g_s[ms->x]);
	ms->a = ms->tmp;
}

void				md5_rounds(t_ssl *ms)
{
	while (++ms->x < 64)
	{
		if (ms->x <= 15)
		{
			ms->f = F(ms->b, ms->c, ms->d);
			ms->g = ms->x;
		}
		else if (ms->x >= 16 && ms->x <= 31)
		{
			ms->f = G(ms->b, ms->c, ms->d);
			ms->g = (5 * ms->x + 1) % 16;
		}
		else if (ms->x >= 32 && ms->x <= 47)
		{
			ms->f = H(ms->b, ms->c, ms->d);
			ms->g = (3 * ms->x + 5) % 16;
		}
		else
		{
			ms->f = I(ms->b, ms->c, ms->d);
			ms->g = (7 * ms->x) % 16;
		}
		adjust_working_var(ms);
	}
}

void				md5_algo(t_ssl *ms)
{
	unsigned int	i;

	i = 0;
	pre_processing(ms);
	while (i < ms->msg_len)
	{
		ms->f = 0;
		ms->g = 0;
		ms->x = -1;
		ms->a = ms->var[0];
		ms->b = ms->var[1];
		ms->c = ms->var[2];
		ms->d = ms->var[3];
		ms->msg32 = (uint32_t*)(ms->msg);
		md5_rounds(ms);
		ms->var[0] += ms->a;
		ms->var[1] += ms->b;
		ms->var[2] += ms->c;
		ms->var[3] += ms->d;
		ms->msg += 64;
		i += 64;
	}
}

void				handle_md5(char **av, int flag)
{
	int				i;
	int				fd;
	t_ssl			ms;

	i = 1;
	ft_bzero(&ms, sizeof(ms));
	while (av[i] && av[i][0] == '-')
		i++;
	if (!isatty(0))
		read_stdin_and_file(0, &ms, av[i]);
	while (av[i])
	{
		if (check_dir(av[i]) == 0)
			ft_printf("%s: %s: Is a directory\n", av[0], av[i]);
		else if (flag & FLAG_S)
		{
			md5_padding((uint8_t*)av[i], ft_strlen(av[i]), &ms);
			md5_algo(&ms);
			print_hash(&ms, av[i]);
		}
		else if (check_file(av[i]) == 0)
			if ((fd = open(av[i], O_RDONLY)) > -1)
				read_stdin_and_file(fd, &ms, av[i]);
		i++;
	}
}
