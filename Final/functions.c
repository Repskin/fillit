/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburnouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:40:06 by tburnouf          #+#    #+#             */
/*   Updated: 2017/10/26 15:53:39 by tburnouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

int		t_result_min(int nb_tetriminos)
{
	int i;

	i = 2;
	while (i * i < nb_tetriminos * 4)
		i++;
	return (i);
}

int		**reduce_piece(int **points_piece, int nb, int reduce)
{
	int i;

	i = 0;
	while (i < 4)
	{
		points_piece[i][reduce] -= nb;
		i++;
	}
	return (points_piece);
}

void	print_result(char **array_soluce, int index)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < index)
	{
		j = 0;
		while (j < index)
		{
			ft_putchar(array_soluce[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}
