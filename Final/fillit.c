/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburnouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:39:41 by tburnouf          #+#    #+#             */
/*   Updated: 2017/10/26 16:06:13 by tburnouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** array	= map of the result
** t		= struct of tetris
** i		= size of the map
**
** Try to place a piece in the map
*/

int			place_piece(char **array, t_tetris *t, int i)
{
	while (!test_place_piece(array, t, i) && t->x < i && t->y < i)
		incrementation(t, i);
	if (t->x >= i)
	{
		t->x = 0;
		t->y = 0;
		if (t->c == 'A')
			return (0);
		t = t->prev;
		incrementation(t, i);
		delete_last_piece(array, i, t->c);
		return (place_piece(array, t, i));
	}
	else if (t->next == NULL)
		return (1);
	return (place_piece(array, t->next, i));
}

/*
** array_pieces	= map of the different coords of pieces
** c			= character of the piece
** prev			= adress of the previous piece
**
** Save the infos of a piece in a struct
*/

t_tetris	*set_pieces(char **array_pieces, char c, t_tetris *prev)
{
	t_tetris	*tetris;
	t_tetris	*t_prev;

	t_prev = prev;
	if (array_pieces[0][0] != '0')
	{
		tetris = malloc(sizeof(t_tetris));
		tetris->c = c;
		tetris->x = 0;
		tetris->y = 0;
		tetris->points = find_points(array_pieces[0], 0, 0);
		tetris->prev = t_prev;
		tetris->next = set_pieces(++array_pieces, ++c, tetris);
	}
	else
		tetris = NULL;
	return (tetris);
}

/*
** a_result	= map of the result
** t		= struct of the tetris (piece info)
** size		= width of the result
**
** Try to place a piece
*/

int			test_place_piece(char **a_result, t_tetris *t, int size)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (!test_point(a_result, t, i, size))
			return (0);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (!place_point(a_result, t, i, size))
			return (0);
		i++;
	}
	return (1);
}

/*
** a_result	= map of the result
** index	= width of the result
** c		= character of the piece
**
** Delete the last piece in the map
*/

void		delete_last_piece(char **a_result, int index, char c)
{
	int i;
	int j;

	i = 0;
	while (i < index)
	{
		j = 0;
		while (j < index)
		{
			if (a_result[i][j] == c)
				a_result[i][j] = '.';
			j++;
		}
		i++;
	}
}

/*
** array_pieces	= array of the differents coords of the piece
** index		= width of the result
**
** Main function of the solver
*/

void		fillit(char **array_pieces, int index)
{
	char			**array_result;
	t_tetris		*tetris;

	tetris = set_pieces(array_pieces, 'A', NULL);
	array_result = initialize(index, index, '.');
	while (!place_piece(array_pieces, tetris, index))
	{
		index++;
		array_result = initialize(index, index, '.');
	}
	print_result(array_pieces, index);
	free(array_result);
}
