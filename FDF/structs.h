/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 19:17:48 by mcamila           #+#    #+#             */
/*   Updated: 2020/01/24 20:15:49 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_pt2
{
	int			x;
	int			y;
}				t_pt2;

typedef struct	s_pt3
{
	double		x;
	double		y;
	double		z;
}				t_pt3;

typedef struct	s_tri
{
	int	pt[3];
}				t_tri;

typedef struct	s_3d_obj
{
	t_pt3		*pt;
	t_tri		*tri;
	int			num_of_pts;
	int			num_of_tris;
}				t_3d_obj;

#endif