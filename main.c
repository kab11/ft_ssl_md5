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

// 1. Parse
// 	-	check for flags
// 	-	determine if is a file or directory
// 		~ if file read info from file
// 		~ else read stdin input 

// struct s_dispatch hashfxns[HASH_COUNT] = {
// 	{"md5", handle_md5},
// 	{"sha256", handle_256},
// 	{"sha512",handle_512}
// };

void startup(int ac, char **av)
{
	int flags;

	(void)ac;
	flags = 0;
	flags |= turn_on_flags(av);
	printf("flag = %d\n", flags);
}

int main(int argc, char **argv)
{
	(void)argv;
	if (argc >= 2)
		startup(argc, argv);
	else
		return(ft_printf("usage: ft_ssl command [-pqrs] [command args]\n"));
	return (0);
}
