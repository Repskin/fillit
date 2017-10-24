/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburnouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:50:05 by tburnouf          #+#    #+#             */
/*   Updated: 2017/10/24 14:50:05 by tburnouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

typedef struct		s_tetris
{
    int				**points;
    char			c;
    int				x;
    int				y;
    struct s_tetris	*next;
}					t_tetris;

// File : tetris.c
void                print_soluce(char **tab_soluce, int index);
void                put_zero_tetris(t_tetris *tetris);
int                 placer_pieces(char **tab_soluce, t_tetris *tetris, int index);
t_tetris            *set_pieces(char **tab_pieces, char c);
int                 t_soluce_min(int nb_tetriminos);

// File : array.c
char                **initialiser(int index, int index2, char c);
char                **reinitialiser(char **tab, int index, int index2, char c);
int                 **initialiser_tab_point_piece(void);
int                 **reduire(int **points_piece, int nb, int reduce);
int                 **formater_point_piece(int **points_piece);

// File : pieces.h
char                **stock_piece(char *str, int nb_tetriminos, int fd);
int                 tester_point(char **tab_soluce, t_tetris *t, int i, int taille_soluce);
int                 placer_point(char **tab_soluce, t_tetris *t, int i, int taille_soluce);
int                 **trouver_points(char *piece, int j, int k);
int                 tester_placer_piece(char **tab_soluce, t_tetris *tetris, int taille_soluce);

// File : functions.c
void                ft_putchar(char c);
void                ft_putstr(char *str);
int                 factorielle(int n);
void                swap(char **a, char **b);
void                swap_int(int *x, int *y);

// File : cal_nbr_comb.c
char                **init_result(int n);
void                init_heap(int n, int *c, char **result, int *numbers);
void                heap_permute(int n, int *numbers, char **result);
char                **chercher_possibilites(int n);

// File : fillit.c
t_tetris            *liste_possibilite(char *str_possibilites, t_tetris *tab_tetris_reel, int i);
t_tetris            *get_tab_tetris(t_tetris tetris, int nb, char **tab_possibilites, int indice);
void                fillit(char **tab_pieces, int index, int nb);
int                 fonction2(char *argv);
char                **trier_tab(char **tab, int debut, int fin, int len);

// File : read_file.c
int                 check_1(char *str, int size);
int                 check_2(char *str);
int                 get_poids(char *str, int len);

#endif
