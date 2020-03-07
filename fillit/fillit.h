/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjasper <bjasper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:20:01 by bjasper           #+#    #+#             */
/*   Updated: 2019/11/12 14:13:32 by bjasper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# define BUFF_SIZE 21

typedef struct			s_fill
{
	int					x_len;
	int					y_len;
	int					sharp[4];
}						t_fill;

typedef struct			s_tet
{
	int					rows[121][4];
	int					length;
}						t_tet;

typedef struct			s_col
{
	int					elem[4];
	int					len;
}						t_col;

typedef	struct			s_main
{
	t_col				cols[144][26];
	unsigned long long	masks[26][26][2];
	t_tet				tets[26];
	int					map_side;
	char				map[12][13];
	int					imax;
}						t_main;

int						ft_y(t_main *main, int i);
int						ft_validity(int fd, char *buf, t_fill *figure);
void					ft_length(t_fill *a);

#endif
