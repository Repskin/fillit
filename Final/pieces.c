/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pieces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburnouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:40:12 by tburnouf          #+#    #+#             */
/*   Updated: 2017/10/26 14:40:13 by tburnouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		**format_point_piece(int **points_piece)
{
	int i;
	int nb;
	
	i = 0;
	nb = 4;
	while (i < 4)
	{
		if (points_piece[i][0] <= nb)
			nb = points_piece[i][0];
		i++;
	}
	points_piece = reduce_piece(points_piece, nb, 0);
	i = 0;
	nb = 4;
	while (i < 4)
	{
		if (points_piece[i][1] <= nb)
			nb = points_piece[i][1];
		i++;
	}
	points_piece = reduce_piece(points_piece, nb, 1);
	return (points_piece);
}

int		test_point(char **array_soluce, t_tetris *t, int i, int size_result)
{
	int		x;
	int		y;
	
	x = t->x + t->points[i][0];
	y = t->y + t->points[i][1];
	if (!(x < size_result) || !(y < size_result) || array_soluce[x][y] != '.')
	{
		return (0);
	}
	return (1);
}

int		place_point(char **array_soluce, t_tetris *t, int i, int size_result)
{
	int		x;
	int		y;
	char	c;
	
	x = t->x + t->points[i][0];
	y = t->y + t->points[i][1];
	c = t->c;
	if (!(x < size_result) || !(y < size_result) || array_soluce[x][y] != '.')
		return (0);
	array_soluce[x][y] = c;
	return (1);
}

int		**find_points(char *piece, int j, int k)
{
	int i;
	int nb_diese;
	int **points_piece;
	
	i = -1;
	nb_diese = 0;
	points_piece = initialize_array_piece();
	while (piece[++i] && nb_diese != 4)
	{
		if (piece[i] == '#')
		{
			points_piece[nb_diese][1] = j;
			points_piece[nb_diese][0] = k;
			nb_diese++;
		}
		if (piece[i] == '\n')
		{
			j = 0;
			k++;
		}
		else
			j++;
	}
	return (format_point_piece(points_piece));
}

void	incrementation(t_tetris *tetris, int index)
{
	if (tetris->y + 1 < index)
		tetris->y++;
	else
	{
		tetris->x++;
		tetris->y = 0;
	}
}
