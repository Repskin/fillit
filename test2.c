/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelpin <afelpin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:24:01 by afelpin           #+#    #+#             */
/*   Updated: 2017/10/12 15:23:45 by afelpin          ###   ########.fr       */
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
	if (str[20] && str[20] != '\n' && str[20] != EOF)
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

int		tester_point(char **tab_soluce, int x, int y, int taille_soluce)
{
	if (!(x < taille_soluce) || !(y < taille_soluce) || tab_soluce[x][y] != '.')
		return (0);
	return (1);
}

int		placer_point(char **tab_soluce, char c, int x, int y, int taille_soluce)
{
	if (!(x < taille_soluce) || !(y < taille_soluce) || tab_soluce[x][y] != '.')
		return (0);
	tab_soluce[x][y] = c;
	return (1);
}


int		tester_piece(char **tab_soluce, char *piece, int taille_soluce, int x, int y)
{
	int i;
	int j;
	int nb_diese;
	int decallage_y;
	int temp_dec_y;
	int temp_i;

	i = 0;
	j = 0;
	decallage_y = 0;
	temp_dec_y = 0;
	nb_diese = 0;
	temp_i = 0;
	while (nb_diese < 4)
	{
		while (piece[i] != '#')
		{
			if (piece[i] == '\n')
			{
				if (nb_diese > 0)
					x++;
				decallage_y = -1;
			}
			else
				decallage_y++;
			i++;
		}
		if (i - temp_i >= 1)
			decallage_y++;
		if (nb_diese > 0 && decallage_y > temp_dec_y)
			y++;
		else if (nb_diese > 0 && decallage_y < temp_dec_y)
			y--;
		temp_dec_y = decallage_y;
		temp_i = i;
		i++;
		//printf("i : %d, temp_i : %d, x : %d, y : %d, decallage_y : %d, temp_dec_y : %d\n", i, temp_i, x, y, decallage_y, temp_dec_y);
		if (!tester_point(tab_soluce, x, y, taille_soluce))
			return (0);
		nb_diese++;
	}
	return (1);
}

int		placer_piece(char **tab_soluce, char *piece, int taille_soluce, int x, int y, char c)
{
	int i;
	int j;
	int nb_diese;
	int decallage_y;
	int temp_dec_y;
	int temp_i;

	i = 0;
	j = 0;
	decallage_y = 0;
	temp_dec_y = 0;
	nb_diese = 0;
	temp_i = 0;
	while (nb_diese < 4)
	{
		while (piece[i] != '#')
		{
			if (piece[i] == '\n')
			{
				if (nb_diese > 0)
					x++;
				decallage_y = -1;
			}
			else
				decallage_y++;
			i++;
		}
		if (i - temp_i >= 1)
			decallage_y++;
		if (nb_diese > 0 && decallage_y > temp_dec_y)
			y++;
		else if (nb_diese > 0 && decallage_y < temp_dec_y)
			y--;
		temp_dec_y = decallage_y;
		temp_i = i;
		i++;
		if (!placer_point(tab_soluce, c, x, y, taille_soluce))
			return (0);
		nb_diese++;
	}
	return (1);
}

int		placer_pieces(char **tab_soluce, char **tab_pieces, int index)
{
	int i;
	char c;
	int x;
	int y;

	i = 0;
	c = 'A';
	x = 0;
	y = 0;

	while (tab_pieces[i][0] != '0' && x < index && y < index)
	{
		if (!tester_piece(tab_soluce, tab_pieces[i], index, x, y))
		{
			if (y+1 < index)
				y++;
			else
			{
				x++;
				y = 0;
			}
		}
		else
		{
			placer_piece(tab_soluce, tab_pieces[i], index, x, y, c);
			i++;
			c++;
		}
	}
	if (tab_pieces[i][0] == '0')
		return (1);
	return (0);
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
