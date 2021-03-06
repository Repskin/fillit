/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelpin <afelpin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 09:56:37 by afelpin           #+#    #+#             */
/*   Updated: 2017/10/09 16:28:02 by afelpin          ###   ########.fr       */
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

/*
** Pour afficher a l'ecran la solution finale
*/
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

/*
** Pour initialiser un tableau de solution de taille index avec des points partout
*/
char	**initiliser_soluce(int index)
{
	int i;
	int j;
	char **y;

	i = 0;
	y = malloc(sizeof(char *) * index);

	while(i < index)
	{
		y[i] = malloc(sizeof(char) * index);
		i++;
	}

	i = 0;
	while (i < index)
	{
		j = 0;
		while (j < index)
		{
			y[i][j] = '.';
			j++;
		}
		i++;
	}
	return (y);
}

int		get_coordonnees(char **tab_soluce, int index)
{
	int i;
	int j;

	i = 0;
	j = 0;

	while (i < index && tab_soluce[i][j] != '.')
	{
		j = 0;
		while (j < index && tab_soluce[i][j] != '.')
		{
			j++;
		}
		if (j >= index)
		{
		  i++;
		  j = 0;
		}
	}
	if (i >= index)
		return (-1);
	i += 1;
	j += 1;
	return (i * j);
}

int		get_position(int id, int previous, char **tab_soluce, int index)
{
	int pos;

	pos = get_coordonnees(tab_soluce, index) + (id - previous);
}

int		placer_point(int id, int previous, char **tab_soluce, char nom, int index)
{
	int i;
	int j;
	int coordonnees;

	i = 0;
	j = 0;
	id = 0;
	if (previous == 0)
	{
		coordonnees = get_coordonnees(tab_soluce, index);
		if (coordonnees == -1)
			return (0);

		tab_soluce[coordonnees / index][coordonnees % index] = nom;
	}
	else
	{
		coordonnees = get_position(id, previous, tab_soluce, index);
		if (coordonnees == -1)
			return (0);
		tab_soluce[coordonnees / index][coordonnees % index] = nom;
	}
	return (1);
}

int		placer_piece(int tab_pieces[][4], char **tab_soluce, int index)
{
	int i;
	int j;
	char nom;
	int previous;

	i = 0;
	nom = 'A';
	previous = 0;
	while (tab_pieces[i][0] != 0)
	{
		j = 0;
		while (j < 4)
		{
			if (!(placer_point(tab_pieces[i][j], previous, tab_soluce, nom, index)))
				return (0);
			previous = tab_pieces[i][j];
			j++;
		}
		nom++;
		i++;
		previous = 0;
	}
	return (1);
}

/*
** Function qui se charge d'appeler les autres fonctions :
** creer un nouveau tableau, essayer de le remplir, l'afficher a l'ecran.
*/
void	fillit(int tab_pieces[][4])
{
	int index;
	char **tab_soluce;
	unsigned char boolean;

	index = 3;
	boolean = 0;

	while (!boolean)
	{
		tab_soluce = initiliser_soluce(index);
		if (!placer_piece(tab_pieces, tab_soluce, index))
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
	int		error;
	int		tab_pieces[26][4];
	int		nb_tetriminos;
	int		size_read_temp;

	size_read = 1;
	nb_tetriminos = 0;
	if (argc != 2)
		return (1);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (2);
	initialiser_tableau(tab_pieces);
	while (size_read > 0)
	{
		size_read_temp = size_read;
		size_read = read(fd, buf, 21);
		if ((error = check_1(buf, size_read)) || (error = check_2(buf)) || nb_tetriminos > 26)
		{
			close(fd);
			return (1);
		}
		if (size_read > 19)
			stock_piece(tab_pieces, nb_tetriminos, buf);
		nb_tetriminos++;
	}
	close(fd);
	if (size_read_temp == 21)
		return (8);
	fillit(tab_pieces);
	return (0);
}
