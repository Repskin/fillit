/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburnouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:40:00 by tburnouf          #+#    #+#             */
/*   Updated: 2017/10/26 16:00:03 by tburnouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** index & index2	= size of the array
** c				= char of the piece
**
** Initialize the map with a char
*/

char	**initialize(int index, int index2, char c)
{
	int		i;
	int		j;
	char	**y;

	i = 0;
	y = malloc(sizeof(char *) * index);
	while (i < index)
	{
		y[i] = malloc(sizeof(char) * index2);
		i++;
	}
	i = 0;
	while (i < index)
	{
		j = 0;
		while (j < index2)
		{
			y[i][j] = c;
			j++;
		}
		i++;
	}
	return (y);
}

/*
** No params
**
** Initialize a map 4x4
*/

int		**initialize_array_piece(void)
{
	int i;
	int **y;

	i = 0;
	y = malloc(sizeof(int *) * 4);
	while (i < 4)
	{
		y[i] = malloc(sizeof(int) * 2);
		i++;
	}
	return (y);
}
