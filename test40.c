/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test40.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelpin <afelpin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:24:01 by afelpin           #+#    #+#             */
/*   Updated: 2017/10/15 11:50:29 by afelpin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

/*
** JUSTE POUR VOIR LE Temps
*/
#include <time.h>

typedef struct		s_tetris
{
	int				**points;
	char			c;
	int				x;
	int				y;
	struct s_tetris	*next;
}					t_tetris;

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

int	check_1(char *str, int size)
{
	int i;
	int p;

	i = 0;
	p = 0;
	if (size == 0)
		return (0);
	if (size < 20 || size > 21)
		return (1);
	while (i < size)
	{
		if (str[i] == '#')
			p++;
		else if (str[i] != '#' && str[i] != '.' && str[i] != '\n')
			return (2);
		i++;
	}
	if (str[4] != '\n' || str[9] != '\n' || str[14] != '\n' || str[19] != '\n')
		return (3);
	if (p != 4)
		return (4);
	if (str[20] && str[20] != '\n' && str[20] != EOF)
		return (5);
	return (0);
}

int	check_2(char *str)
{
	int i;
	int connection;

	i = 0;
	connection = 0;
	while (str[i])
	{
		if (str[i] == '#')
		{
			if (str[i + 1] && str[i + 1] == '#')
				connection++;
			if (str[i - 1] && str[i - 1] == '#')
				connection++;
			if (str[i + 5] && str[i + 5] == '#')
				connection++;
			if (str[i - 5] && str[i - 5] == '#')
				connection++;
		}
		i++;
	}
	if (connection != 6 && connection != 8)
		return (1);
	return (0);
}

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
			{
				tetris->y++;
			}
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

t_tetris	**get_tab_tetris(t_tetris *tetris, int index)
{
	t_tetris	**tab_tetris;

	tab_tetris = malloc(sizeof(t_tetris*) * (index + 1));
	tetris = NULL;
	return (tab_tetris);
}

void	fillit(char **tab_pieces, int index)
{
	char			**tab_soluce;
	unsigned char	boolean;
	t_tetris		*tetris;
	t_tetris		**tab_tetris;
	int				i;

	boolean = 0;
	i = 0;
	tetris = set_pieces(tab_pieces, 'A');
	tab_tetris = get_tab_tetris(tetris, index);
	while (!boolean)
	{
		while (tab_tetris[i] && !boolean)
		{
			tab_soluce = initialiser(index, index, '.');
			if (!placer_pieces(tab_soluce, tab_tetris[i], index))
				i++;
			else
				boolean = 1;
		}
		index++;
		i = 0;
	}
	print_soluce(tab_soluce, index);
}

int	fonction2(char *argv)
{
	int		fd;
	int		size_read;
	char	buf[22];
	int		nb_tetriminos;
	int		size_read_temp;

	size_read = 1;
	nb_tetriminos = 0;
	if ((fd = open(argv, O_RDONLY)) < 0)
		return (0);
	while ((size_read = read(fd, buf, 21)) > 0)
	{
		size_read_temp = size_read;
		if ((check_1(buf, size_read)) || (check_2(buf)) || nb_tetriminos > 26)
		{
			close(fd);
			return (0);
		}
		nb_tetriminos++;
	}
	if (size_read_temp != 20)
		return (0);
	close(fd);
	return (nb_tetriminos);
}

int	main(int argc, char **argv)
{
	/*
	** JUSTE POUR VOIR LE TEMPS
	*/
	long clk_tck = CLOCKS_PER_SEC;
    clock_t t1, t2;
	t1 = clock();

	int	nb;

	if (argc != 2)
	{
		ft_putstr("usage: ./fillit <file>\n");
		return (2);
	}
	if ((nb = fonction2(argv[1])))
		fillit(stock_piece(argv[1], nb, 0), t_soluce_min(nb));
	else
		ft_putstr("error\n");

	/*
	** JUSTE POUR VOIR LE Temps
	*/
	t2 = clock();
	printf("--------------------\nTemps (s) : %lf \n", (double)(t2-t1)/(double)clk_tck);
	return (0);
}
