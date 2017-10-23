/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test60.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelpin <afelpin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 15:24:46 by afelpin           #+#    #+#             */
/*   Updated: 2017/10/23 13:42:21 by afelpin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int		ft_strlen(const char *s)
{
	int		length;

	length = 0;
	while (s[length])
		length++;
	return (length);
}

int		factorielle(int nb)
{
	int		i;

	i = nb - 1;
	while (i > 1)
		nb *= i--;
	return (nb);
}

int		check_double(char *str)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (str[i])
	{
		c = str[i];
		j = i + 1;
		while (str[j])
		{
			if (str[i] == str[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	print_tab_possibilites(char **tab_possibilites, int x, int y)
{
	int		i;
	int		j;

	i = 0;
	while (i < x)
	{
		j = 0;
		while (j < y)
		{
			printf("%c", tab_possibilites[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
}

void	remplir_tab(char *str, char **tab_possibilites)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tab_possibilites[i][0] != '0')
		i++;
	while (str[j])
	{
		tab_possibilites[i][j] = str[j];
		j++;
	}
}

void	faire_combi(char *str, char *tmp, int ind, char **tab_possibilites)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	if (ind >= len)
	{
		if (check_double(tmp))
			remplir_tab(tmp, tab_possibilites);
		return ;
	}
	while (i < len)
	{
		tmp[ind] = str[i];
		faire_combi(str, tmp, ind + 1, tab_possibilites);
		i++;
	}
}

void    swap(char **a, char **b)
{
    char     *tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

int		get_poids(char *str, int len)
{
	char	c;
	int		poids_lettre;
	int		poids;
	int 	pos;
	int		i;

	poids = 0;
	i = 0;
	while (i < len)
	{
		poids_lettre = 0;
		pos = len - i;
		c = str[i];
		while (c < ('A' + len))
		{
			poids_lettre = (poids_lettre * len) +  1;
			c++;
		}
		//printf("Poids lettre : %d, pos : %d\n", poids_lettre, pos);
		poids += poids_lettre * pos;
		i++;
	}
	return (poids);
}

char	**trier_tab_possibilites(char **tab_possibilites, int taille_soluce, int len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < taille_soluce - 1)
	{
		j = 0;
		while (j < taille_soluce - 1)
		{
			if (get_poids(tab_possibilites[j], len) < get_poids(tab_possibilites[j + 1], len))
				swap(&tab_possibilites[j], &tab_possibilites[j + 1]);
			j++;
		}
		i++;
	}
	return (tab_possibilites);
}

char	**trouver_possibilites(char *str, int i)
{
	int		len;
	char	*tmp;
	char	**tab_possibilites;
	int		j;
	int		facto;

	len = ft_strlen(str);
	facto = factorielle(len);
	tmp = malloc(sizeof(char) * (len + 1));
	tab_possibilites = malloc(sizeof(char*) * facto);
	while (i < facto)
	{
		j = 0;
		tab_possibilites[i] = malloc(sizeof(char) * len);
		while (j < len)
			tab_possibilites[i][j++] = '0';
		i++;
	}
	faire_combi(str, tmp, 0, tab_possibilites);
	free(tmp);
	return (trier_tab_possibilites(tab_possibilites, facto, len));
}

char	**chercher_possibilites(int nb_pieces)
{
	char	*str;
	char	c;
	int		i;
	char	**tab_soluces;

	c = 'A';
	str = malloc(sizeof(char) * (nb_pieces + 1));
	i = 0;
	while (i < nb_pieces)
	{
		str[i] = c++;
		i++;
	}
	str[i] = '\0';
	tab_soluces = trouver_possibilites(str, 0);
	return (tab_soluces);
}

/*int		main(void)
{
	int poids;

	poids = get_poids("BCAD", 4);
	printf("%d\n", poids);
	return (0);
}*/
