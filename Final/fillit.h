/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburnouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:46:07 by tburnouf          #+#    #+#             */
/*   Updated: 2017/10/26 14:46:08 by tburnouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct		s_tetris
{
	int				**points;
	char			c;
	int				x;
	int				y;
	struct s_tetris	*next;
	struct s_tetris	*prev;
}					t_tetris;

/*
** File : array.c 
*/
char				**initialize(int index, int index2, char c);
int					**initialize_array_piece(void);

/*
** File : fillit.c
*/
int					place_piece(char **array, t_tetris *t, int i);
t_tetris			*set_pieces(char **array_pieces, char c, t_tetris *prev);
int					test_place_piece(char **array_soluce, t_tetris *tetris, int size_result);
void				delete_last_piece(char **array_soluce, int index, char c);
void				fillit(char **array_pieces, int index);

/*
** File : functions.c
*/
void				ft_putchar(char c);
void				ft_putstr(char *str);
int					t_result_min(int nb_tetriminos);
int					**reduce_piece(int **points_piece, int nb, int reduce);
void				print_result(char **array_soluce, int index);

/*
** File : pieces.c
*/
int					**format_point_piece(int **points_piece);
int					test_point(char **array_soluce, t_tetris *t, int i, int size_result);
int					place_point(char **array_soluce, t_tetris *t, int i, int size_result);
int					**find_points(char *piece, int j, int k);
void				incrementation(t_tetris *tetris, int index);

/*
** File : read_file.c
*/
int					grid_is_good(char *str, int size);
int					shape_is_good(char *str);
char				**stock_piece(char *str, int nb_tetriminos, int fd);
int					reader(char *argv);

#endif
