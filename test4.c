//
//  test4.c
//  
//
//  Created by Theo Burnouf on 10/13/17.
//
//

#include <stdio.h>

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

int     **combinaisons(n)
{
    int **result;
    int i;
    int j;
    int k;
    int l;
    int m;
    
    i = 0;
    j = 0;
    k = 0;
    l = 0;
    m = n - 1;
    result = malloc(sizeof(int*) * factorielle(n));
    while (i < factorielle(n))
    {
        result[i] = malloc(sizeof(int) * n);
        i++;
    }
    i = 0;
    while (i < n)
    {
        result[0][i] = n - i;
        i++;
    }
    i = 1;
    while (result[i])
    {
        if ((m + 1) >= n)
        {
            k = result[i][m];
            while (m > 0)
            {
                result[i][m] = result[i-1][m-1];
                m--;
            }
            j = 0;
            result[i][m] = k;
        }
        else
        {
            while (result[i][j] != result[i][m+1])
            {
                result[i][j] = result[i-1][j];
                j++;
            }
            k = result[i][j];
            while (l > j)
            {
                result[i][l] = result[i-1][l-1];
                l--;
            }
            m++;
            result[i][m] = k;
            m = n - 1;
            j = 0;
        }
        i++;
    }
}

int     main(void)
{
    combinaisons(3);
    return (0);
}
