/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjasper <bjasper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:20:01 by bjasper           #+#    #+#             */
/*   Updated: 2019/11/08 18:47:37 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

//#include "libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

# define BUFF_SIZE 21

typedef struct	s_fill
{
    int			x_len;
    int			y_len;
    int			sharp[4];
}            	t_fill;

typedef struct 	s_Tet
{
	int			rows[121][4];
	int			length;
}				t_Tet;

t_Tet			tets[26];

typedef struct 	s_Col
{
	int			elem[4];
	int			len;
}				t_Col;

int				map_side;

t_Col			cols[144][26];
unsigned long long	masks[26][26][2];

char			map[12][13];

#endif