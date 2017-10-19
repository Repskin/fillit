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

void printArr(int a[], int n, int **result)
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
}

// Generating permutation using Heap Algorithm
void heapPermutation(int a[], int size, int n, int **result)
{
    int i;
    
    i = 0;
    if (size == 1)
    {
        printArr(a, n, result);
        return;
    }
    while (i < size)
    {
        heapPermutation(a, size-1, n, result++);
        
        // if size is odd, swap first and last
        // element
        if (size%2==1)
            swap(&a[0], &a[size-1]);
        
        // If size is even, swap ith and last
        // element
        else
            swap(&a[i], &a[size-1]);
        i++;
    }
}

int     main(void)
{
    int **result;
    int *num;
    int i;
    int j;
    int n;
    
    n = 5;
    i = n;
    result = init_result(n);
    num = malloc(sizeof(int) * n);
    while (i > 0)
    {
        num[i-1] = i;
        i--;
    }
    heapPermutation(num, n, n, result);
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
