/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_md5_sha.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 16:19:29 by kblack            #+#    #+#             */
/*   Updated: 2019/07/12 16:19:42 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

// void print_hash(t_ssl *ms)
// {
//     // printf("inside print\n");
//     int i;

//     i = -1;
//     while (++i < 4)
//         printf("%.8x", convert_to_big_endian(ms->var[i]));
//     printf("\n");
// }

// char *join_algo_output(t_ssl *ms)
// {
//     int i;
//     char *tmp;
//     char *hash;

//     i = -1;
//     tmp = NULL;
//     hash = NULL;
//     while (++i < 4)
//     {
//         tmp = hash;
        
//         free(tmp);
//     }
//     printf("final hash = %s\n", hash);
//     return (hash);
// }

void tranform_to_big_endian(t_ssl *ms)
{
    ms->var[0] = convert_to_big_endian(ms->var[0]);
    ms->var[1] = convert_to_big_endian(ms->var[1]);
    ms->var[2] = convert_to_big_endian(ms->var[2]);
    ms->var[3] = convert_to_big_endian(ms->var[3]);
}

void print_hash(t_ssl *ms, char* input)
{
    tranform_to_big_endian(ms);
    if (ms->flag & FLAG_S)
    {
        BIT_OFF(ms->flag, FLAG_S);
        if (ms->flag & FLAG_R)
            ft_printf("")
        ft_printf("MD5 (\"%s\") = ", input);
    }
    else if (ms->flag & FLAG_P)
        ft_printf("%s", input);
    else
        ft_printf("MDS (%s) = ", input);
    ft_printf("%.8x%.8x%.8x%.8x", ms->var[0], ms->var[1], ms->var[2], ms->var[3]);
    printf("\n");
}