#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	ft_strlen(const char *s)
{
	int length;

	length = 0;
	while (s[length])
		length++;
	return (length);
}

int	factorielle(int nb)
{
	int i;

	i = nb - 1;
	while (i > 1)
		nb *= i--;
	return (nb);
}

int	check_double(char *str)
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
	int i;
	int j;

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
	int i;
	int j;

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
	int i;
	int len;

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

char	**trouver_possibilites(char *str)
{
	int		len;
	char	*tmp;
	char	**tab_possibilites;
	int		i;
	int		j;

	i = 0;
	len = ft_strlen(str);
	tmp = malloc(sizeof(char) * (len + 1));
	tab_possibilites = malloc(sizeof(char*) * factorielle(len));
	while (i < factorielle(len))
	{
		j = 0;
		tab_possibilites[i] = malloc(sizeof(char) * len);
		while (j < len)
			tab_possibilites[i][j++] = '0';
		i++;
	}
	faire_combi(str, tmp, 0, tab_possibilites);
	free(tmp);
	return (tab_possibilites);
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
	tab_soluces = trouver_possibilites(str);
	//print_tab_possibilites(tab_soluces, factorielle(nb_pieces), nb_pieces);
	return (tab_soluces);
}
