//
//  test4.c
//
//
//  Created by Theo Burnouf on 10/13/17.
//
//

#include <stdio.h>
#include <stdlib.h>

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

/*void printArr(int a[], int n, int **result)
{
    int i;
    int j;
    
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
}*/

void    heap_permute(int n, int *numbers, int **result)
{
    int *c;
    int i;
    int j;
    int k;
    
    c = malloc(sizeof(int) * n);
    i = 0;
    j = 0;
    k = 0;
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
                swap(&numbers[0], &numbers[i]);
            else
                swap(&numbers[c[i]], &numbers[i]);
            while (k <  n)
            {
                result[j][k] = numbers[k];
                k++;
            }
            j++;
            k = 0;
            c[i]++;
            i = 0;
        }
        else
        {
            c[i] = 0;
            i++;
        }
    }
}

int     main(int argc, char **argv)
{
    int **result;
    int *num;
    int i;
    int j;
    int n;
    
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
    return (0);
}
