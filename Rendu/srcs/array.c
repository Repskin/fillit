/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburnouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:46:19 by tburnouf          #+#    #+#             */
/*   Updated: 2017/10/24 14:46:20 by tburnouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

char	**initialiser(int index, int index2, char c)
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

char	**reinitialiser(char **tab, int index, int index2, char c)
{
    int i;
    int j;
    
    i = 0;
    while (i < index)
    {
        j = 0;
        while (j < index2)
        {
            tab[i][j] = c;
            j++;
        }
        i++;
    }
    return (tab);
}

int	**initialiser_tab_point_piece(void)
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

int	**reduire(int **points_piece, int nb, int reduce)
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

int	**formater_point_piece(int **points_piece)
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
    points_piece = reduire(points_piece, nb, 0);
    i = 0;
    nb = 4;
    while (i < 4)
    {
        if (points_piece[i][1] <= nb)
            nb = points_piece[i][1];
        i++;
    }
    points_piece = reduire(points_piece, nb, 1);
    return (points_piece);
}
