/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburnouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 14:54:32 by tburnouf          #+#    #+#             */
/*   Updated: 2017/10/06 14:54:34 by tburnouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

/*
 int main(int argc, char **argv)
 
 Return O
 
 Params :
 int argc       = numbers of arguments when the program is open
 char **argv    = array which contains the arguments
 
 Main function which handle the program
*/
int     main(int argc, char **argv)
{
    int     fd;
    int     size_read;
    char    buf[22];
    int     error;
    int     array_pieces[26][4];
    int     nb_tetriminos;
    
    size_read = 1;
    nb_tetriminos = 0;
    if (argc != 2)
        return (0);
    if ((fd = open(argv[1], O_RDONLY)) < 0)
        return (0);
    init_shape_array(array_pieces);
    while (size_read > 0)
    {
        size_read = read(fd, buf, 21);
        if (!(error = check_grid(buf, size_read)) || !(error = check_shape(buf)) || nb_tetriminos > 26)
        {
            close(fd);
            return (0);
        }
        if (size_read > 19)
            put_shape_array(array_pieces, nb_tetriminos, buf);
        nb_tetriminos++;
    }
    close(fd);
    return (0);
}
