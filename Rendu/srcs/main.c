/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburnouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:39:36 by tburnouf          #+#    #+#             */
/*   Updated: 2017/10/24 14:39:37 by tburnouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int	main(int argc, char **argv)
{
    /*
     ** JUSTE POUR VOIR LE TEMPS
     */
    long clk_tck = CLOCKS_PER_SEC;
    clock_t t1, t2;
    t1 = clock();
    
    int	nb;
    
    if (argc != 2)
    {
        ft_putstr("usage: ./fillit <file>\n");
        return (2);
    }
    if ((nb = fonction2(argv[1])))
        fillit(stock_piece(argv[1], nb, 0), t_soluce_min(nb), nb);
    else
        ft_putstr("error\n");
    
    /*
     ** JUSTE POUR VOIR LE Temps
     */
    t2 = clock();
    printf("\n");
    printf("Temps : %lfs \n", (double)(t2-t1)/(double)clk_tck);
    return (0);
}
