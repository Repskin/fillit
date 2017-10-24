/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburnouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:39:17 by tburnouf          #+#    #+#             */
/*   Updated: 2017/10/24 14:39:18 by tburnouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

t_tetris	*liste_possibilite(char *str_possibilites, t_tetris *tab_tetris_reel, int i)
{
    t_tetris	*tetris;
    
    if (str_possibilites[i])
    {
        tetris = malloc(sizeof(t_tetris));
        tetris = &tab_tetris_reel[(int)(str_possibilites[i] - 65)];
        tetris->next = liste_possibilite(str_possibilites, tab_tetris_reel, ++i);
    }
    else
        tetris = NULL;
    return (tetris);
}

t_tetris	*get_tab_tetris(t_tetris tetris, int nb, char **tab_possibilites, int indice)
{
    int			i;
    t_tetris	*pt_tetris;
    t_tetris	*tab_tetris_reel;
    
    i = 0;
    pt_tetris = &tetris;
    tab_tetris_reel = malloc(sizeof(t_tetris) * nb);
    while (i < nb)
    {
        tab_tetris_reel[i] = *pt_tetris;
        pt_tetris = pt_tetris->next;
        i++;
    }
    return (liste_possibilite(tab_possibilites[indice], tab_tetris_reel, 0));
}

void	fillit(char **tab_pieces, int index, int nb)
{
    char			**tab_soluce;
    unsigned char	boolean;
    t_tetris		*tetris;
    char			**tab_possibilites;
    int				i;
    
    boolean = 0;
    tetris = set_pieces(tab_pieces, 'A');
    tab_possibilites = chercher_possibilites(nb);
    for (int z = 0; z < factorielle(nb); z++)
    {
        printf("%s\n", tab_possibilites[z]);
    }
    printf("\n");
    while (!boolean)
    {
        i = 0;
        while (i < factorielle(nb) && !boolean)
        {
            tab_soluce = initialiser(index, index, '.');
            if (!placer_pieces(tab_soluce, get_tab_tetris(*tetris, nb, tab_possibilites, i), index))
                i++;
            else
            {
                //printf("%s\n\n", tab_possibilites[i]);
                //printf("Solution :\n");
                print_soluce(tab_soluce, index);
                boolean = 1;
            }
        }
        index++;
    }
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

char	**trier_tab(char **tab, int debut, int fin, int len)
{
    int gauche;
    int droite;
    char *pivot;
    
    gauche = debut - 1;
    droite = fin + 1;
    pivot = tab[debut];
    if (debut >= fin)
        return (tab);
    while (1)
    {
        droite--;
        gauche++;
        //while (get_poids(tab[droite], len) > get_poids(pivot, len))
        while (get_poids(pivot, len) > get_poids(tab[droite], len))
            droite--;
        //while (get_poids(tab[gauche], len) < get_poids(pivot, len))
        while (get_poids(pivot, len) < get_poids(tab[gauche], len))
            gauche++;
        if (gauche < droite)
            swap(&tab[gauche], &tab[droite]);
        else
            break;
    }
    tab = trier_tab(tab, debut, droite, len);
    tab = trier_tab(tab, droite + 1, fin, len);
    return (tab);
}
