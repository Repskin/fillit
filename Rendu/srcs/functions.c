/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburnouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:40:36 by tburnouf          #+#    #+#             */
/*   Updated: 2017/10/24 14:40:37 by tburnouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

void	ft_putchar(char c)
{
    write(1, &c, 1);
}

void	ft_putstr(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        ft_putchar(str[i]);
        i++;
    }
}

int     factorielle(int n)
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

void	swap(char **a, char **b)
{
    char *tmp;
    
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void    swap_int(int *x, int *y)
{
    int temp;
    
    temp = *x;
    *x = *y;
    *y = temp;
}
