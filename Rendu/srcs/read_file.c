/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburnouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:38:15 by tburnouf          #+#    #+#             */
/*   Updated: 2017/10/24 14:38:18 by tburnouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

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

int		get_poids(char *str, int len)
{
    char	c;
    int		poids_lettre;
    int		poids;
    int		pos;
    int		i;
    
    poids = 0;
    i = 0;
    len--;
    while (i < len)
    {
        poids_lettre = 0;
        pos = len - i;
        c = str[i];
        while (c < ('A' + len))
        {
            poids_lettre = (poids_lettre * len) + 1;
            c++;
        }
        poids += poids_lettre * pos;
        i++;
    }
    return (poids);
}
