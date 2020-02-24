/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 02:00:33 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/22 06:08:25 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

t_inst_obj		*make_obj_inst(t_ref_obj *r, float x, float y, float z);
t_camera		initialize_camera(float d);
t_matrix		make_transform_matrix(t_inst_obj obj);
t_pt2			make_pt2_from_v3(t_vec3 vec, float d);
void			put_pixel(int x, int y, int color, t_data *data);
void			color_loop(t_ref_obj *obj, unsigned int speed);
void			swap_f(float *a, float *b);
void			swap_2pt(t_pt2 *a, t_pt2 *b);
void			swap_colors(t_color *a, t_color *b);
float			absolute(float x);
void			error(int error, t_data *data, t_maps *maps);
int				color_add_1(t_color *c, t_ref_obj *obj, int i);
int				color_add_2(t_color *c, t_ref_obj *obj, int i);
int				color_add_3(t_color *c, t_ref_obj *obj, int i);
int				color_add_4(t_color *c, t_ref_obj *obj, int i);
int				color_add_5(t_color *c, t_ref_obj *obj, int i);
int				color_add_6(t_color *c, t_ref_obj *obj, int i);
int				color_add_11(t_color *c, t_ref_obj *obj, int i);
int				color_add_22(t_color *c, t_ref_obj *obj, int i);
int				color_add_33(t_color *c, t_ref_obj *obj, int i);
t_sc_tri		mk_sc_tri(t_sp_tri sp, t_data *data, t_inst_obj obj, t_tri tri);
t_vec3			seek_tri_center(t_vec3 vertex1, t_vec3 vertex2, t_vec3 vertex3);
t_sp_tri		make_tri_in_space(t_inst_obj obj, t_tri tri, float d);
void			initializate_s_1(t_pt2 p0, t_pt2 p1, t_pt2 p2, t_draw *s);
void			initializate_s_2(t_pt2 p1, t_pt2 p2, t_draw *s);
void			initializate_a(t_pt2 p0, t_pt2 p1, t_pt2 p2, t_draw *s);
void			draw_tri_2(t_draw *s, t_data *data, int y);
void			draw_tri_1(t_draw *s, t_data *data, int y);
void			draw_hor_line(t_draw s, int y, t_data *data);
void			initializate_a(t_pt2 p0, t_pt2 p1, t_pt2 p2, t_draw *s);
float			absolute(float x);
void			swap_colors(t_color *a, t_color *b);
void			swap_2pt(t_pt2 *a, t_pt2 *b);
void			swap_f(float *a, float *b);
void			draw_pixel(int y, t_data *data, t_hln *ln);
void			initializate_ln(t_hln *ln, t_draw *s);
void			color_loop(t_ref_obj *obj, unsigned int speed);
t_camera		initialize_camera(float d);
void			put_pixel(int x, int y, int color, t_data *data);
void			error(int error, t_data *data, t_maps *maps);
void			*pmalloc(t_data *data, t_maps *maps, size_t size);
t_ref_obj		make_ref_obj_from_map(int x, int y, t_data *data, t_maps *maps);
void			go_away(t_data *data);
void			render_frame(t_inst_obj *objects, int num_of_obj, t_data *data);
void			draw_tri(t_pt2 p0, t_pt2 p1, t_pt2 p2, t_data *data);
int				mouse_press(int button, int x, int y, t_data *data);
int				key_release(int key, t_data *data);
int				key_press(int key, t_data *data);
int				x_press(void *data);
void			make_tris(t_ref_obj *obj, t_maps *maps, int x, int y);
void			del_maps(t_maps *maps);

#endif
