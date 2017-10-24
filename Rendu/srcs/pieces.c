/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pieces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburnouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:45:04 by tburnouf          #+#    #+#             */
/*   Updated: 2017/10/24 14:45:05 by tburnouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

char	**stock_piece(char *str, int nb_tetriminos, int fd)
{
    char	**tab_pieces;
    char	buf[(nb_tetriminos + 1) * 21];
    int		i;
    int		j;
    int		pos_tab;
    
    fd = open(str, O_RDONLY);
    i = 0;
    pos_tab = 0;
    tab_pieces = initialiser(nb_tetriminos + 1, 21, '0');
    read(fd, buf, (nb_tetriminos) * 21);
    while (pos_tab < nb_tetriminos)
    {
        j = 0;
        while (j <= 20)
        {
            tab_pieces[pos_tab][j] = buf[i];
            j++;
            i++;
        }
        pos_tab++;
    }
    return (tab_pieces);
}

int		tester_point(char **tab_soluce, t_tetris *t, int i, int taille_soluce)
{
    int		x;
    int		y;
    
    x = t->x + t->points[i][0];
    y = t->y + t->points[i][1];
    if (!(x < taille_soluce) || !(y < taille_soluce) || tab_soluce[x][y] != '.')
    {
        return (0);
    }
    return (1);
}

int		placer_point(char **tab_soluce, t_tetris *t, int i, int taille_soluce)
{
    int		x;
    int		y;
    char	c;
    
    x = t->x + t->points[i][0];
    y = t->y + t->points[i][1];
    c = t->c;
    if (!(x < taille_soluce) || !(y < taille_soluce) || tab_soluce[x][y] != '.')
        return (0);
    tab_soluce[x][y] = c;
    return (1);
}

int	**trouver_points(char *piece, int j, int k)
{
    int i;
    int nb_diese;
    int **points_piece;
    
    i = -1;
    nb_diese = 0;
    points_piece = initialiser_tab_point_piece();
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
    return (formater_point_piece(points_piece));
}

int	tester_placer_piece(char **tab_soluce, t_tetris *tetris, int taille_soluce)
{
    int i;
    
    i = 0;
    while (i < 4)
    {
        if (!tester_point(tab_soluce, tetris, i, taille_soluce))
            return (0);
        i++;
    }
    i = 0;
    while (i < 4)
    {
        if (!placer_point(tab_soluce, tetris, i, taille_soluce))
            return (0);
        i++;
    }
    return (1);
}
