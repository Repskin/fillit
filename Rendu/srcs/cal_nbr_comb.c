/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal_nbr_comb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburnouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:38:47 by tburnouf          #+#    #+#             */
/*   Updated: 2017/10/24 14:38:48 by tburnouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

char     **init_result(int n)
{
    char **result;
    int i;
    int j;
    int nb_comb;
    
    i = 0;
    j = 0;
    nb_comb = factorielle(n);
    result = malloc(sizeof(int*) * nb_comb);
    while (i < nb_comb)
    {
        result[i] = malloc(sizeof(int) * n);
        i++;
    }
    i = 0;
    while (i < nb_comb)
    {
        while (j < n)
        {
            result[i][j] = 'A';
            j++;
        }
        j = 0;
        i++;
    }
    return (result);
}

void    init_heap(int n, int *c, char **result, int *numbers)
{
    int i;
    
    i = 0;
    while (i < n)
    {
        c[i] = 0;
        i++;
    }
    i = 0;
    while (i < n)
    {
        result[0][i] = (char)(numbers[i] + '@');
        i++;
    }
}

void    heap_permute(int n, int *numbers, char **result)
{
    int *c;
    int i;
    int j;
    int k;
    
    c = malloc(sizeof(int) * n);
    i = 0;
    j = 1;
    k = 0;
    init_heap(n, c, result, numbers);
    while (i < n)
    {
        if (c[i] < i)
        {
            if (i % 2 == 0)
                swap_int(&numbers[0], &numbers[i]);
            else
                swap_int(&numbers[c[i]], &numbers[i]);
            while (k <  n)
            {
                result[j][k] = (char)(numbers[k] + '@');
                k++;
            }
            j++;
            k = 0;
            c[i]++;
            i = 0;
        }
        else
            c[i++] = 0;
    }
}

char	**chercher_possibilites(int n)
{
    char **result;
    int *num;
    int i;
    
    i = n;
    result = init_result(n);
    num = malloc(sizeof(int) * n);
    while (i > 0)
    {
        num[i-1] = i;
        i--;
    }
    heap_permute(n, num, result);
    result = trier_tab(result, 0, factorielle(n) - 1, n);
    return (result);
}
