//
//  test4.c
//
//
//  Created by Theo Burnouf on 10/13/17.
//
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int len;

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

/*int     **combinaisons(int n)
 {
 int **result;
 int i;
 int j;
 int nb_comb;
 int tmp;
 
 i = 0;
 j = 0;
 nb_comb = factorielle(n);
 tmp = 0; // Valeur temp
 pos = 1; // Position de notre chiffre
 result = malloc(sizeof(int*) * nb_comb);
 while (i < nb_comb)
 {
 result[i] = malloc(sizeof(int) * n);
 i++;
 }
 i = 0;
 while (i < n)
 {
 result[j][i] = n - i;
 i++;
 }
 i = 1;
 while (i < nb_comb)
 {
 if (pos > (n - 1))
 {
 tmp = result[i-1][pos-1];
 while (pos > 1)
 {
 result[i][pos-1] = result[i-1][pos-2];
 pos--;
 }
 pos--;
 j = 0;
 result[i][pos] = tmp;
 }
 else
 {
 while (j < (pos - 1))
 {
 result[i][j] = result[i-1][j];
 j++;
 }
 result[i][j] = result[i-1][j+1];
 result[i][j+1] = result[i-1][j];
 j += 2;
 while (j <= (n - 1))
 {
 result[i][j] = result[i-1][j];
 j++;
 }
 pos++;
 }
 j = 0;
 i++;
 }
 return (result);
 }*/

int     **init_result(int n)
{
    int **result;
    int i;
    int nb_comb;
    
    i = 0;
    nb_comb = factorielle(n);
    result = malloc(sizeof(int*) * nb_comb);
    while (i < nb_comb)
    {
        result[i] = malloc(sizeof(int) * n);
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

/*int     **combinaisons2(int **result, int n)
{
    int num[n];
    int tmp;
    int i;
    int j;
    int k;
    int l;
    
    i = n;
    j = 1;
    k = 0;
    while (i > 0)
    {
        num[i-1] = i;
        i--;
    }
    while (j <= n)
    {
        i = 0;
        while (i < n-1)
        {
            tmp = num[i];
            num[i] = num[i+1];
            num[i+1] = tmp;
            l = 0;
            while (l < n)
            {
                result[k][l] = num[l];
                l++;
            }
            i++;
            k++;
        }
        j++;
    }
    return (result);
}*/

int     **combinaisons3(/*int **result, */int v[], int n)
{
    /*int i;
    int j;
    
    i = 0;
    j = 0;
    if (n == 1) {
        result[i] = v;
    }
    else {
        while (i < n)
        {
            combinaisons3(result++, v, n-1);
            if (n % 2 == 1)
                swap(&v[0], &v[n-1]);
            else
                swap(&v[i], &v[n-1]);
            i++;
        }
    }
    return (result);*/
}
void print(const int *v)
{
    int i;
    int size = len;
    if (v != 0) {
        for ( i = 0; i < size; i++) {
            printf("%4d", v[i] );
        }
        printf("\n");
    }
}
void heappermute(int v[], int n) {
    int i;
    if (n == 1) {
        print(v);
    }
    else {
        for (i = 0; i < n; i++) {
            heappermute(v, n-1);
            if (n % 2 == 1) {
                swap(&v[0], &v[n-1]);
            }
            else {
                swap(&v[i], &v[n-1]);
            }
        }
    }
}

int     main(void)
{
    int **result;
    int *num;
    int i;
    int j;
    int n;
    
    i = 0;
    j = 0;
    n = 5;
    num = malloc(sizeof(int) * n);
    i = n;
    while (i > 0)
    {
        num[i-1] = i;
        i--;
    }
    i = 0;
    result = init_result(n);
    heappermute(/*result, */num, n);
    /*while (i < factorielle(n))
    {
        while (j < n)
        {
            printf("%d", result[i][j]);
            j++;
        }
        j = 0;
        printf("\n");
        i++;
    }*/
    return (0);
}
