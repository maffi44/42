/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 02:00:33 by mcamila           #+#    #+#             */
/*   Updated: 2020/01/30 03:54:43 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

//t_vec3	pt3_add(t_vec3 pt1, t_vec3 pt2);
t_inst_obj	make_obj_inst(t_ref_obj *ref);
t_camera	initialize_camera(float d);
t_matrix	make_transform_matrix(t_camera cam, t_inst_obj obj);
t_pt2		make_pt2_from_v3(t_vec3 vec);

#endif /* FUNCTIONS_H */