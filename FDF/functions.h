/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 02:00:33 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/21 12:53:55 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

//t_vec3	pt3_add(t_vec3 pt1, t_vec3 pt2);
t_inst_obj	*make_obj_inst(t_ref_obj *ref, float x_sc, float y_sc, float z_sc);
t_camera	initialize_camera(float d);
t_matrix	make_transform_matrix(t_camera cam, t_inst_obj obj);
t_pt2		make_pt2_from_v3(t_vec3 vec, float d);
void 		put_pixel(int x, int y, int color, t_data *data);
void		color_loop(t_ref_obj *obj, unsigned int speed);
void		swap_f(float *a, float *b);
void		swap_2pt(t_pt2 *a, t_pt2 *b);
void		swap_colors(t_color *a, t_color *b);
void		swap(int* a , int*b);
float		absolute(float x );
void		error(int error, t_data *data, t_maps *maps);

int color_add_1(t_color *c, t_ref_obj *obj, int i);
int color_add_2(t_color *c, t_ref_obj *obj, int i);
int color_add_3(t_color *c, t_ref_obj *obj, int i);
int color_add_4(t_color *c, t_ref_obj *obj, int i);
int color_add_5(t_color *c, t_ref_obj *obj, int i);
int color_add_6(t_color *c, t_ref_obj *obj, int i);
int color_add_11(t_color *c, t_ref_obj *obj, int i);
int color_add_22(t_color *c, t_ref_obj *obj, int i);
int color_add_33(t_color *c, t_ref_obj *obj, int i);

t_sc_tri	mk_sc_tri(t_sp_tri sp, t_data *data, t_inst_obj obj, t_tri tri);
t_vec3			seek_tri_center(t_vec3 vertex1, t_vec3 vertex2, t_vec3 vertex3);
t_sp_tri		make_tri_in_space(t_inst_obj obj, t_tri tri, float d);
void	initializate_s_1(t_pt2 p0, t_pt2 p1, t_pt2 p2, t_draw *s);
void	initializate_s_2(t_pt2 p0, t_pt2 p1, t_pt2 p2, t_draw *s);
void	initializate_a(t_pt2 p0, t_pt2 p1, t_pt2 p2, t_draw *s);


#endif /* FUNCTIONS_H */