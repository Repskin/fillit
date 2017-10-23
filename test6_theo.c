/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test6_theo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburnouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 14:58:23 by tburnouf          #+#    #+#             */
/*   Updated: 2017/10/23 09:14:23 by tburnouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int     **init_result(int n)
{
    int **result;
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
            result[i][j] = 0;
            j++;
        }
        j = 0;
        i++;
    }
    return (result);
}

void    swap(int *x, int *y)
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
    while (i < n)
    {
        c[i] = 0;
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

void    heap_permute(int n, int *numbers, int **result)
{
    int *c;
    int i;
    int j;
    int k;
    
    c = malloc(sizeof(int) * n);
    init_value(&i, &j, &k);
    init_heap(n, c, result, numbers);
    while (i < n)
    {
        if (c[i] < i)
        {
            if (i % 2 == 0)
                swap(&numbers[0], &numbers[i]);
            else
                swap(&numbers[c[i]], &numbers[i]);
            while (k++ < n)
                result[j][k] = numbers[k];
            update_value(&j, &k, c, &i);
        }
        else
            c[i++] = 0;
    }
}

int     main(int argc, char **argv)
{
    int **result;
    int *num;
    int i;
    int j;
    int n;
    
    long clk_tck = CLOCKS_PER_SEC;
    clock_t t1, t2;
    t1 = clock();
    
    if (argc != 2)
        return (0);
    n = atoi(argv[1]);
    i = n;
    result = init_result(n);
    num = malloc(sizeof(int) * n);
    while (i > 0)
    {
        num[i-1] = i;
        i--;
    }
    heap_permute(n, num, result);
    i = 0;
    j = 0;
    while (i < factorielle(n))
    {
        while (j < n)
        {
            printf("%d", result[i][j]);
            j++;
        }
        j = 0;
        printf("\n");
        i++;
    }
    t2 = clock();
    printf("Temps : %lfs\n", (double)(t2-t1)/(double)clk_tck);
    return (0);
}
