/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburnouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:39:47 by tburnouf          #+#    #+#             */
/*   Updated: 2017/10/26 15:53:57 by tburnouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	main(int argc, char **argv)
{
	int	nb;

	if (argc != 2)
	{
		ft_putstr("usage: ./fillit <file>\n");
		return (2);
	}
	if ((nb = reader(argv[1])))
		fillit(stock_piece(argv[1], nb, 0), t_result_min(nb));
	else
		ft_putstr("error\n");
	return (0);
}
