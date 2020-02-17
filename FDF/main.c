/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:21:28 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/17 22:53:21 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	go_away(t_data *data)
{
	if (data)
	{
		if (data->mlx_ptr && data->img_ptr)
			mlx_destroy_image(data->mlx_ptr, data->img_ptr);
		if (data->zbuff)
			free(data->zbuff);
		if (data->obj_inst)
		{
			if (data->obj_inst->ref_obj)
			{
				if (data->obj_inst->ref_obj->tri)
					free(data->obj_inst->ref_obj->tri);
				if (data->obj_inst->ref_obj->vertex)
					free(data->obj_inst->ref_obj->vertex);
			}
			free(data->obj_inst);
		}
		if (data->mlx_ptr)
			free(data->mlx_ptr);
		if (data->win_ptr)
			free(data->win_ptr);
		free(data);
	}
	exit(0);
}



int	key_press(int key, t_data *data)
{
	if (key == 53)
		go_away(data);
	else if (key == 15)
		data->R_bool = 1;
	else if (key == 12)
			data->Q_bool = !(data->Q_bool);
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
		data->obj_inst->scale.elem[0][0] *= 1.05f;
		data->obj_inst->scale.elem[1][1] *= 1.05f;
		data->obj_inst->scale.elem[2][2] *= 1.05f;
		render_frame(data->obj_inst, 1, data);
	}
	if (button == 5)
	{
		data->obj_inst->scale.elem[0][0] *= 0.95f;
		data->obj_inst->scale.elem[1][1] *= 0.95f;
		data->obj_inst->scale.elem[2][2] *= 0.95f;
		render_frame(data->obj_inst, 1, data);
	}
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
					data->obj_inst->y_ang -= (float) (y - data->y) / 150,
					data->obj_inst->x_ang += (float) (x - data->x) / 150
					);
		}
		else
		{
			data->obj_inst->translate.elem[0][3] += (float) (x - data->x) / 50;
			data->obj_inst->translate.elem[1][3] += (float) (y - data->y) / 50;
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

int frame_loop(t_data *data)
{
	render_frame(data->obj_inst, 1, (void*)data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (argc != 2)
		go_away(data);
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
	t_ref_obj main_obj = map_parser(argv[1], data);

	t_inst_obj	*insts;
	insts = make_obj_inst(&main_obj, 0.01f, 0.01f, 0.01f, 0, 0, 1);
//	insts[1] = make_obj_inst(&obj);
	//insts[0].rotation = make_rotation_matrix(0, 1);

	data->obj_inst = insts;
	data->camera = initialize_camera(1);
	render_frame(insts, 1, data);

//	mlx_hook(data->win_ptr, 12, 0, expose, data);

	mlx_hook(data->win_ptr, 2, 0, key_press, (void*)data);
	mlx_hook(data->win_ptr, 3, 0, key_release, (void*)data);
	mlx_hook(data->win_ptr, 4, 0, mouse_press, (void*)data);
	mlx_hook(data->win_ptr, 5, 0, mouse_release, (void*)data);
	mlx_hook(data->win_ptr, 6, 0, mouse_move, (void*)data);
	mlx_loop_hook(data->mlx_ptr, frame_loop, data);
	mlx_hook(data->win_ptr, 17, 0, x_press, data);

	mlx_loop(data->mlx_ptr);
	return (0);
}
