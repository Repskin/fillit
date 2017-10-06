/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburnouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 16:09:53 by tburnouf          #+#    #+#             */
/*   Updated: 2017/10/05 16:36:14 by tburnouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

// File : srcs/read_file.c
int     check_grid(char *str, int size);
int     check_shape(char *str);
int     init_shape_array(int shape_array[][4]);
int     put_shape_array(int tab[][4], int index, char *buf);

#endif
