/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburnouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:39:52 by tburnouf          #+#    #+#             */
/*   Updated: 2017/10/26 14:39:53 by tburnouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		grid_is_good(char *str, int size)
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

int		shape_is_good(char *str)
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
	tab_pieces = initialize(nb_tetriminos + 1, 21, '0');
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

int		reader(char *argv)
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
		if ((grid_is_good(buf, size_read)) || (shape_is_good(buf)))
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
