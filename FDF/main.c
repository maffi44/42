/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:21:28 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/05 15:17:47 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	go_away(t_data *data)
{
	if (data)
	{
		if (data->mlx_ptr)
			free(data->mlx_ptr);
		if (data->win_ptr)
			free(data->win_ptr);
		free(data);
		data = NULL;
	}
	exit(0);
}

int expose(t_data *data)
{
//	render_frame(data->obj_inst, 1, data);
//	if (((t_data*)data)->mouse_bool)
//		mlx_pixel_put(((t_data*)data)->mlx_ptr, ((t_data*)data)->win_ptr, ((t_data*)data)->x, ((t_data*)data)->y, 0x00FFFFFF);
	return (0);
}

int	key_press(int key, t_data *data)
{
	if (key == 53)
		go_away(data);
	else if (key == 15)
		data->R_bool = 1;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == 15)
		data->R_bool = 0;
	return (0);
}

int mouse_press(int button, int x, int y, t_data *data)
{
	if (button == 1)
	{
		((t_data *) data)->mouse_bool = 1;
		((t_data *) data)->x = x;
		((t_data *) data)->y = y;
	}
	if (button == 4)
	{
		data->obj_inst->scale.elem[0][0] += 0.1f;
		data->obj_inst->scale.elem[1][1] += 0.1f;
		data->obj_inst->scale.elem[2][2] += 0.1f;
		render_frame(data->obj_inst, 1, data);
	}
	if (button == 5)
	{
		data->obj_inst->scale.elem[0][0] *= 0.9f;
		data->obj_inst->scale.elem[1][1] *= 0.9f;
		data->obj_inst->scale.elem[2][2] *= 0.9f;
		render_frame(data->obj_inst, 1, data);
	}
	//	if (((t_data *) data)->mouse_bool == 0) {
	//		((t_data *) data)->mouse_bool = 1;
//			((t_data *) data)->x = x;
//			((t_data *) data)->y = y;
		/*
		else if (((t_data *) data)->mouse_bool == 1)
		{
			((t_data *) data)->mouse_bool = 2;
//			draw_line(((t_data *) data)->x, ((t_data *) data)->y, x, y, data, 0x00FFFFFF);
			((t_data *) data)->x1 = x;
			((t_data *) data)->y1 = y;
		}
		else
		{
			((t_data *) data)->mouse_bool = 0;
			draw_tri(
					((t_data *) data)->x,
					((t_data *) data)->y,
					0,
					((t_data *) data)->x1,
					((t_data *) data)->y1,
					0.1f,
					x,
					y,
					1.0f,
					data
			);
		}*/
//	}
	return (0);
}

int	mouse_release(int button, int x, int y, void *data)
{
	if (button == 1)
		((t_data *) data)->mouse_bool = 0;
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	if (((t_data*)data)->mouse_bool)
	{
		if (data->R_bool)
		{
			data->obj_inst->rotation = make_rotation_matrix(
					data->obj_inst->y_ang -= (double) (y - data->y) / 150,
					data->obj_inst->x_ang += (double) (x - data->x) / 150
					);
		}
		else
		{
			data->obj_inst->translate.elem[0][3] += (double) (x - data->x) / 50;
			data->obj_inst->translate.elem[1][3] += (double) (y - data->y) / 50;
		}

		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		render_frame(data->obj_inst, 1, data);

		((t_data*)data)->x = x;
		((t_data*)data)->y = y;
	}
	return (0);
}

int	x_press(void *data)
{
	go_away(data);
	return (0);
}

int	main() {
	t_data	*data;

//	double z_buff[WIDTH][HIEGHT];

	if (!(data = (t_data*)malloc(sizeof(t_data))))
		go_away(data);
	if (!(data->mlx_ptr = mlx_init()))
		go_away(data);
	if (!(data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HIEGHT, "FDF")))
		go_away(data);
	if (!(data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HIEGHT)))
		go_away(data);
	if (!(data->zbuff = (float*)ft_memalloc(sizeof(float) * WIDTH * HIEGHT)))
		go_away(data);

	bzero(data->zbuff, sizeof(float) * WIDTH * HIEGHT);

	data->dir_light.elem[0] = 0;
	data->dir_light.elem[1] = 0;
	data->dir_light.elem[2] = 0;
	data->dir_light.elem[3] = 1;

	data->mouse_bool = 0;
	data->R_bool = 0;
	data->img_data = mlx_get_data_addr(data->img_ptr,
			&(data->bpp),
			&(data->img_line),
			&(data->endian));
	t_ref_obj obj;

	obj.vertex = (t_vec3*)malloc(sizeof(t_vec3) * 8);
	obj.tri = (t_tri*)malloc(sizeof(t_tri) * 12);
	obj.num_of_pts = 8;
	obj.num_of_tris = 12;

	obj.vertex[0] = make_vertex(-2, -2, -2);
	obj.vertex[1] = make_vertex(-2, 2, -2);
	obj.vertex[2] = make_vertex(2, 2, -2);
	obj.vertex[3] = make_vertex(2, -2, -2);
	obj.vertex[4] = make_vertex(-2, -2, 2);
	obj.vertex[5] = make_vertex(-2, 2, 2);
	obj.vertex[6] = make_vertex(2, 2, 2);
	obj.vertex[7] = make_vertex(2, -2, 2);

	obj.tri[0].pt[0] = 0;
	obj.tri[0].pt[1] = 1;
	obj.tri[0].pt[2] = 2;

	obj.tri[1].pt[0] = 0;
	obj.tri[1].pt[1] = 2;
	obj.tri[1].pt[2] = 3;

	obj.tri[2].pt[0] = 3;
	obj.tri[2].pt[1] = 2;
	obj.tri[2].pt[2] = 7;

	obj.tri[3].pt[0] = 7;
	obj.tri[3].pt[1] = 2;
	obj.tri[3].pt[2] = 6;

	obj.tri[4].pt[0] = 6;
	obj.tri[4].pt[1] = 4;
	obj.tri[4].pt[2] = 7;

	obj.tri[5].pt[0] = 6;
	obj.tri[5].pt[1] = 5;
	obj.tri[5].pt[2] = 4;

	obj.tri[6].pt[0] = 5;
	obj.tri[6].pt[1] = 1;
	obj.tri[6].pt[2] = 4;

	obj.tri[7].pt[0] = 1;
	obj.tri[7].pt[1] = 0;
	obj.tri[7].pt[2] = 4;

	obj.tri[8].pt[0] = 1;
	obj.tri[8].pt[1] = 5;
	obj.tri[8].pt[2] = 2;

	obj.tri[9].pt[0] = 2;
	obj.tri[9].pt[1] = 5;
	obj.tri[9].pt[2] = 6;

	obj.tri[10].pt[0] = 0;
	obj.tri[10].pt[1] = 3;
	obj.tri[10].pt[2] = 4;

	obj.tri[11].pt[0] = 3;
	obj.tri[11].pt[1] = 7;
	obj.tri[11].pt[2] = 4;

	t_inst_obj	*insts;
	insts = (t_inst_obj*)malloc(sizeof(t_inst_obj) * 2);
	insts[0] = make_obj_inst(&obj);
	insts[1] = make_obj_inst(&obj);
	//insts[0].rotation = make_rotation_matrix(0, 1);

	data->obj_inst = insts;
	data->camera = initialize_camera(1);
	render_frame(insts, 1, data);

	mlx_hook(data->win_ptr, 2, 0, key_press, data);
	mlx_hook(data->win_ptr, 3, 0, key_release, data);
	mlx_hook(data->win_ptr, 4, 0, mouse_press, data);
	mlx_hook(data->win_ptr, 5, 0, mouse_release, data);
	mlx_hook(data->win_ptr, 6, 0, mouse_move, data);
	mlx_hook(data->win_ptr, 12, 0, expose, data);
	mlx_hook(data->win_ptr, 17, 0, x_press, data);

	mlx_loop(data->mlx_ptr);
	return (0);
}
