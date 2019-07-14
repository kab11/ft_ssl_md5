/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:19:45 by kblack            #+#    #+#             */
/*   Updated: 2019/04/05 14:19:48 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** 1. Parse
** 	-	check for flags
** 	-	determine if is a file or directory
** 		~ if file read info from file
** 		~ else read stdin input
** 2. Append the padding bits
** 	-	len = 64 < multiple of 512 (448 % 512)
** 	-	is always performed even if message is already 448 mod 512
** 3. A 64-bit representation of the length of the message is
**	  appended to the result of step 2. If the length of the
**	  message is greater than 2^64, only the low-order 64 bits
**    will be used
** 4. Initialize MD buffers, buffers are used to compute the message
**	  digest; each is initalized to the following values in hex,
**	  low-order bytes first;
**    		A: 01	23	45	67
**    		B: 89	ab	cd  ef
**    		C: fe   dc  ba  98
**    		D: 76	54	32	10
**    (Buffer size = 32 bit, 4 buffers)
** 5. Processes message in 16-word blocks; each function takes
**	  in 32-bit words and produces a 32-bit word output
**    		F(X,Y,Z) - (X & Y) | (~X & Z)
**    		G(X,Y,Z) - (X & Z) | (Y & ~Z)
**    		H(X,Y,Z) - X ^ Y ^ Z
**    		I(X.Y.Z) - Y ^ (X | ~Z)
*/

struct s_dispatch hashfxns[HASH_COUNT] = {
	{"md5", handle_md5},
	{"sha256", handle_256}
};

int		startup(int ac, char **av)
{
	int	i;
	int	j;
	int flag;

	i = -1;
	flag = turn_on_flags(av);
	while (++i < ac)
	{
		j = -1;
		while (++j < HASH_COUNT)
		{
			if (ft_strcmp(av[i], hashfxns[j].key) == 0)
			{
				hashfxns[j].fxnptr(av + i, flag);
				return (1);
			}
		}
	}
	if (j > HASH_COUNT)
		ft_printf("ft_ssl:Error: '%s' is an invalid command.\n
			Message Digest commands\nmd5\t sha256\n", av[1]);
	return (0);
}

int		main(int argc, char **argv)
{
	if (argc < 2)
		return (ft_printf("usage: ft_ssl command [-pqrs] [command args]\n"));
	else
		startup(argc, argv);
	return (0);
}
