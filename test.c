/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelpin <afelpin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 09:56:37 by afelpin           #+#    #+#             */
/*   Updated: 2017/10/06 11:12:29 by afelpin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

/*
** Pour verifier que la piece lue a bien le bon nombre et les bon caracteres
*/
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

/*
** Pour verifier que la piece lue a bien 6 ou 8 connecitons
*/
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

/*
** Pour initialiser le tableau de pieces à 0
*/
void	initialiser_tableau(int tab[][4])
{
	int i;
	int j;

	i = 0;
	while (i < 26)
	{
		j = 0;
		while (j < 4)
		{
			tab[i][j] = 0;
			j++;
		}
		i++;
	}
}

/*
** Pour stocker chaque piece lue dans le tableau
*/
void	stock_piece(int tab[][4], int index, char *buf)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 1;
	while (i < 19)
	{
		if (buf[i] == '#')
		{
			tab[index][j] = k;
			j++;
		}
		if (!(buf[i] == '\n'))
			k++;
		i++;
	}
}

int		main(int argc, char **argv)
{
	int		fd;
	int		size_read;
	char	buf[22];
	int		error;
	int		tab_pieces[26][4];
	int		nb_tetriminos;

	size_read = 1;
	nb_tetriminos = 0;
	if (argc != 2)
		return (1);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (2);
	//tab_pieces = initialise_tab_pieces();
	initialiser_tableau(tab_pieces);
	while (size_read > 0)
	{
		size_read = read(fd, buf, 21);
		//printf("%d\n", size_read);
		if ((error = check_1(buf, size_read)) || (error = check_2(buf)) || nb_tetriminos > 26)
		{
			//printf("\nFailed : %d\n", error);
			close(fd);
			return (1);
		}
		if (size_read > 19)
			stock_piece(tab_pieces, nb_tetriminos, buf);
		nb_tetriminos++;
	}
	/*for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 4; j++) {
			printf("%d - ", tab_pieces[i][j]);
		}
		printf("\n");
	}*/
	//printf("OK pour les tests !\n");
	close(fd);
	return (0);
}
