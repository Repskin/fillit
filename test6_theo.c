<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test6_theo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburnouf <tburnouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 14:58:23 by tburnouf          #+#    #+#             */
/*   Updated: 2017/10/23 16:58:53 by afelpin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
=======
//
//  test4.c
//
//
//  Created by Theo Burnouf on 10/13/17.
//
//
>>>>>>> 99ae7d811b280b4ffa87cd6c90511e60761d6ace

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int     factorielle(n)
{
    int result;

    result = n;
    while (n > 1)
    {
        n -= 1;
        result = result * n;
    }
    return (result);
}

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
            result[i][j] = 0 + 'A';
            j++;
        }
        j = 0;
        i++;
    }
    return (result);
}

void    swap_b(int *x, int *y)
{
    int temp;

    temp = *x;
    *x = *y;
    *y = temp;
}

void    init_heap(int n, int *c, int **result, int *numbers)
{
    int i;

    i = 0;
    while (result[i])
    {
        j = 0;
        if (result[i][0] == 0)
            while (result[i][j])
            {
                result[i][j] = a[j];
                j++;
            }
        i++;
    }
    i = 0;
    while (i < n)
    {
        result[0][i] = numbers[i];
        i++;
    }
}

void    init_value(int *i, int *j, int *k)
{
    *i = 0;
    *j = 1;
    *k = -1;
}

void    update_value(int *j, int *k, int *c, int *i)
{
    *j += 1;
    *k = -1;
    c[*i]++;
    *i = 0;
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
        c[i] = 0;
        i++;
    }
    while (k <  n)
    {
        result[j][k] = numbers[k];
        k++;
    }
    j++;
    k = 0;
    i = 0;
    while (i < n)
    {
        if (c[i] < i)
        {
            if (i % 2 == 0)
                swap_b(&numbers[0], &numbers[i]);
            else
                swap_b(&numbers[c[i]], &numbers[i]);
            while (k++ < n)
                result[j][k] = numbers[k] + 'A' - 1;
            update_value(&j, &k, c, &i);
        }
        else
        {
            c[i] = 0;
            i++;
        }
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
<<<<<<< HEAD
	result = trier_tab(result, 0, factorielle(n) - 1, n);
	/*for (int z = 0; z < factorielle(n); z++)
	{
		for (int w = 0; w < n; w++)
			printf("%c", result[z][w]);
		printf(", ");
	}*/
    return (result);
=======
    /*i = 0;
    j = 0;
    while (i < factorielle(n))
    {
        while (j < n)
        {
            printf("%c", result[i][j]);
            j++;
        }
        j = 0;
        printf("\n");
        i++;
    }*/
    printf("\n\n%d Lignes affichees\n", i);
    return (0);
>>>>>>> 99ae7d811b280b4ffa87cd6c90511e60761d6ace
}
