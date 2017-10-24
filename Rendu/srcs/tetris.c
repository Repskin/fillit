/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburnouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:48:45 by tburnouf          #+#    #+#             */
/*   Updated: 2017/10/24 14:48:45 by tburnouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

void	print_soluce(char **tab_soluce, int index)
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
            ft_putchar(tab_soluce[i][j]);
            j++;
        }
        ft_putchar('\n');
        i++;
    }
}


void	put_zero_tetris(t_tetris *tetris)
{
    tetris->x = 0;
    tetris->y = 0;
}

int	placer_pieces(char **tab_soluce, t_tetris *tetris, int index)
{
    while (tetris != NULL && tetris->x < index && tetris->y < index)
    {
        if (!tester_placer_piece(tab_soluce, tetris, index))
        {
            if (tetris->y + 1 < index)
                tetris->y++;
            else
            {
                tetris->x++;
                tetris->y = 0;
            }
        }
        else
        {
            put_zero_tetris(tetris);
            tetris = tetris->next;
        }
    }
    if (tetris == NULL)
        return (1);
    put_zero_tetris(tetris);
    return (0);
}

t_tetris	*set_pieces(char **tab_pieces, char c)
{
    t_tetris	*tetris;
    
    if (tab_pieces[0][0] != '0')
    {
        tetris = malloc(sizeof(t_tetris));
        tetris->c = c;
        tetris->x = 0;
        tetris->y = 0;
        tetris->points = trouver_points(tab_pieces[0], 0, 0);
        tetris->next = set_pieces(++tab_pieces, ++c);
    }
    else
        tetris = NULL;
    return (tetris);
}

int	t_soluce_min(int nb_tetriminos)
{
    int i;
    
    i = 2;
    while (i * i < nb_tetriminos * 4)
        i++;
    return (i);
}
