/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburnouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 13:54:56 by tburnouf          #+#    #+#             */
/*   Updated: 2017/10/06 13:54:58 by tburnouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

/*
** check_grid(char *str, int size)
**
** Return an integer
** 0 if the grid is wrong
** 1 if the grid is good
**
** Params :
** char *str  = the string of the piece
** int size   = the numbers of characters read
**
** Check if the grid have 4 characters #
** Check if the grid have the good number of characters
*/
int     check_grid(char *str, int size)
{
    int i;
    int p;
    
    i = 0;
    p = 0;
    if (size == 0) // If the function read didn't read a char
        return (1);
    if (size < 20 || size > 21) // If the number of char is wrong
        return (0);
    while (i < size)
    {
        if (str[i] == '#')
            p++;
        else if (str[i] != '#' && str[i] != '.' && str[i] != '\n')
            return (0);
        i++;
    }
    if (str[4] != '\n' || str[9] != '\n' ||
        str[14] != '\n' || str[19] != '\n')
        return (0);
    if (p != 4) // If there is more or less than 4 #
        return (0);
    if (str[20] && str[20] != '\n') // If the last char is not a \n
        return (0);
    return (1);
}

/*
 check_shape(char *str)
 
 Return an integer
 0 if the shape is wrong
 1 if the shape is good
 
 Params :
 char *str  = the string of the piece
 
 Check if all of the characters # is connected in a grid 4x4
*/
int     check_shape(char *str)
{
    int i;
    int link;
    
    i = 0;
    link = 0;
    while (str[i])
    {
        if (str[i] == '#')
        {
            if (str[i + 1] && str[i + 1] == '#') // Check the right case
                link++;
            if (str[i - 1] && str[i - 1] == '#') // Check the left case
                link++;
            if (str[i + 5] && str[i + 5] == '#') // Check the bottom case
                link++;
            if (str[i - 5] && str[i - 5] == '#') // Check the top case
                link++;
        }
        i++;
    }
    if (link != 6 && link != 8)
        return (0);
    return (1);
}

/*
 init_shape_array(int shape_array[][4])
 
 Return nothing
 
 Params :
 int shape_array[][4]   = an empty int array
 
 Initialize an int array which contains the position of each characters # for each pieces
*/
void    init_shape_array(int shape_array[][4])
{
    int i;
    int j;
    
    i = 0;
    while (i < 26) // For each pieces
    {
        j = 0;
        while (j < 4) // For each characters #
            shape_array[i][j++] = 0;
        i++;
    }
}

/*
 put_shape_array(int tab[][4], int index, char *buf)
 
 Return nothing
 
 Params :
 int tab[][4]   = an initialized int array with 0
 int index      = the number of the piece
 char *buf      = the string who contains the piece
 
 Put in an int array the position of each characters # of the pieces
*/
void    put_shape_array(int tab[][4], int index, char *buf)
{
    int i;
    int j;
    int k;
    
    i = 0;
    j = 0;
    k = 1;
    while(i < 19)
    {
        if (buf[i] == '#')
            tab[index][j++] = k;
        if (buf[i] != '\n')
            k++;
        i++;
    }
}
