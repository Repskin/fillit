/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburnouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 14:58:23 by tburnouf          #+#    #+#             */
/*   Updated: 2017/10/08 14:58:25 by tburnouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

/*
** print_solution(char **array_solution, int index)
**
** Return nothing
**
** Params :
** char **array_solution  = array which contains the solution
** int index              = integer which contains the width of the solution
**
** Function which print the array of the solution
*/
void    print_solution(int **array_solution, int index)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (i < index)
    {
        j = 0;
        while (j < index)
        {
            ft_putchar(array_solution[i][j]);
            j++;
        }
        ft_putchar('\n');
        i++;
    }
}

/*
** **initialize_solution(int index)
**
** Return a string array
**
** Params :
** int index  = integer which contains the with of the solution
**
** Function which initialize the array of the solution
*/
char    **initialize_solution(int index)
{
    int     i;
    int     j;
    char    **result;
    
    i = 0;
    result = malloc(sizeof(char*) * index);
    while (i < index)
    {
        result[i] = malloc(sizeof(char) * index);
        i++;
    }
    i = 0;
    while (i < index)
    {
        j = 0;
        while (j < index)
        {
            result[i][j] = '.';
            j++;
        }
        i++;
    }
    return (result);
}

/*
** count_pieces(int array_pieces[][4])
**
** Return an integer with the number of pieces
**
** Params :
** int array_pieces[][4]   = an int array which contains each pieces
**
** Function which return the number of pieces
*/
int     count_pieces(int array_pieces[][4])
{
    int i;
    
    i = 0;
    while (array_pieces[i])
        i++;
    return (i);
}
