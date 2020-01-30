/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 12:42:03 by mcamila           #+#    #+#             */
/*   Updated: 2020/01/30 03:02:08 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

t_vec3	pt3_add(t_vec3 pt1, t_vec3 pt2)
{
	pt1.x += pt2.x;
	pt1.y += pt2.y;
	pt1.z += pt2.z;
	return (pt1);
}

t_inst_obj	make_obj_inst(t_ref_obj *ref)
{
	t_inst_obj	new_inst;

	new_inst.ref_obj = ref;
	new_inst.scale = {{1, 0, 0, 0,}, {0, 1, 0, 0}, {0, 0, 1, 0}, (0, 0, 0, 1)};
	new_inst.rotation = {{1, 0, 0, 0,}, {0, 1, 0, 0}, {0, 0, 1, 0}, (0, 0, 0, 1)};
	new_inst.translate = {{0, 0, 0, 1,}, {0, 0, 0, 1}, {0, 0, 0, 1}, (0, 0, 0, 1)};
	return (new_inst);
}

t_camera	initialize_camera(float d)
{
	t_camera cam;
	cam.translation = {{0, 0, 0, 1,}, {0, 0, 0, 1}, {0, 0, 0, 1}, (0, 0, 0, 1)};
	cam.rotation = {{1, 0, 0, 0,}, {0, 1, 0, 0}, {0, 0, 1, 0}, (0, 0, 0, 1)};
	cam.projection = {{}, {}, {}, {0, 0, 0, 0,}};
	cam.d = d;

	return (cam);
}