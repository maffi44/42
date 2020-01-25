/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 19:17:48 by mcamila           #+#    #+#             */
/*   Updated: 2020/01/25 14:40:24 by mcamila          ###   ########.fr       */
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

typedef struct	s_ref_obj
{
	t_pt3		*pt;
	t_tri		*tri;
	int			num_of_pts;
	int			num_of_tris;
}				t_ref_obj;

typedef struct	s_inst_obj
{
	t_ref_obj	*ref;
	t_pt3		translate;
}				t_inst_obj;


t_pt3	pt3_add(t_pt3 pt1, t_pt3 pt2);

#endif