/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelpin <afelpin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:24:01 by afelpin           #+#    #+#             */
/*   Updated: 2017/10/10 18:04:08 by afelpin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


void	ft_putchar(char c)
{
	write(1, &c, 1);
}


int		check_1(char *str, int size)
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
	if (str[20] && str[20] != '\n')
		return (5);
	return (0);
}


int		check_2(char *str)
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
	int i;
	int j;
	char **y;

	i = 0;
	y = malloc(sizeof(char *) * index);

	while(i < index)
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


char	**stock_piece(char *str, int nb_tetriminos)
{
	char **tab_pieces;
	char buf[(nb_tetriminos + 1) * 21];
	int	i;
	int j;
	int pos_tab;
	int fd;

	fd = open(str, O_RDONLY);
	i = 0;
	pos_tab = 0;
	tab_pieces = initialiser(nb_tetriminos+1, 21, '0');
	read(fd, buf, nb_tetriminos * 21 - 1);
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


int		placer_point(char **tab_soluce, char c, int x, int y)
{
	if (tab_soluce[x][y] != '.')
		return (0);
	tab_soluce[x][y] = c;
	return (1);
}


int		placer_piece(char **tab_soluce, char *piece, int taille_soluce, int pos, char c)
{
	int point_placer;

	point_placer = 0;
	while (point_placer != 4)
	{
		if (!placer_point(tab_soluce, c, pos / taille_soluce, pos % taille_soluce))
			return (0);
		pos++;
		point_placer++;
	}
	piece = NULL;
	return (1);
}


int		placer_pieces(char **tab_soluce, char **tab_pieces, int index)
{
	int i;
	char c;

	i = 0;
	c = 'A';

	while (tab_pieces[i][0] != '0')
	{
		if (!placer_piece(tab_soluce, tab_pieces[i], index, 0, c))
			return (0);
		i++;
		c++;
	}
	return (1);
}


void	fillit(char **tab_pieces)
{
	int index;
	char **tab_soluce;
	unsigned char boolean;

	index = 3;
	boolean = 0;

	while (!boolean)
	{
		tab_soluce = initialiser(index, index, '.');
		if (!placer_pieces(tab_soluce, tab_pieces, index))
			index++;
		else
			boolean = 1;
	}
	print_soluce(tab_soluce, index);
}


int		main(int argc, char **argv)
{
	int		fd;
	int		size_read;
	char	buf[22];
	int		nb_tetriminos;
	int		size_read_temp;

	size_read = 1;
	nb_tetriminos = 0;
	if (argc != 2 || (fd = open(argv[1], O_RDONLY)) < 0)
		return (2);
	while (size_read > 0)
	{
		size_read_temp = size_read;
		size_read = read(fd, buf, 21);
		if ((check_1(buf, size_read)) || (check_2(buf)) || nb_tetriminos > 26)
		{
			close(fd);
			return (1);
		}
		nb_tetriminos++;
	}
	if (size_read_temp == 21)
		return (8);
	fillit(stock_piece(argv[1], nb_tetriminos-1));
	close(fd);
	return (0);
}
