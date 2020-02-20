/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:21:28 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/20 20:46:35 by mcamila          ###   ########.fr       */
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
	else if (key == 4)
		data->H_bool = 1;
	else if (key == 3)
		data->F_bool = 1;
	else if (key == 24)
		data->disco++;
	else if (key == 27)
		if (data->disco > 0)
			data->disco--;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == 15)
		data->R_bool = 0;
	else if (key == 4)
		data->H_bool = 0;
	else if (key == 3)
		data->F_bool = 0;
	return (0);
}

void	mouse_scale_p(t_data *data)
{
	if (data->H_bool)
	{
		data->obj_inst->scale.elem[1][1] *= 0.95f;
	}
	else if (data->F_bool)
	{
		if ((data->d += 0.05f) > 4)
			data->d = 4;
	}
	else
	{
		data->obj_inst->scale.elem[0][0] *= 0.95f;
		data->obj_inst->scale.elem[1][1] *= 0.95f;
		data->obj_inst->scale.elem[2][2] *= 0.95f;
	}
}

void	mouse_scale_m(t_data *data)
{
	if (data->H_bool)
	{
		data->obj_inst->scale.elem[1][1] *= 1.05f;
	}
	else if (data->F_bool)
	{
		if ((data->d -= 0.05f) < 0.1f)
			data->d = 0.1f;
	}
	else
	{
		data->obj_inst->scale.elem[0][0] *= 1.05f;
		data->obj_inst->scale.elem[1][1] *= 1.05f;
		data->obj_inst->scale.elem[2][2] *= 1.05f;
	}
}

int		mouse_press(int button, int x, int y, t_data *data)
{
	if (button == 1)
	{
		((t_data *)data)->mouse_bool = 1;
		((t_data *)data)->x = x;
		((t_data *)data)->y = y;
	}
	if (button == 4)
	{
		mouse_scale_m(data);
		render_frame(data->obj_inst, 1, data);
	}
	if (button == 5)
	{
		mouse_scale_p(data);
		render_frame(data->obj_inst, 1, data);
	}
	return (0);
}

int	mouse_release(int button, int x, int y, void *data)
{
	if (button == 1)
		((t_data *)data)->mouse_bool = 0;
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	if (((t_data*)data)->mouse_bool)
	{
		if (data->R_bool)
		{
			data->obj_inst->rotation = make_rotation_matrix(
					data->obj_inst->y_ang -= (float)(y - data->y) / 150,
					data->obj_inst->x_ang += (float)(x - data->x) / 150);
		}
		else
		{
			data->obj_inst->translate.elem[0][3] += (float)(x - data->x) / 50;
			data->obj_inst->translate.elem[1][3] += (float)(y - data->y) / 50;
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

int		frame_loop(t_data *data)
{
	render_frame(data->obj_inst, 1, (void*)data);
	return (0);
}

void	inicializate_data(t_data *data)
{
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
	data->d = 1;
	data->mouse_bool = 0;
	data->R_bool = 0;
	data->F_bool = 0;
	data->H_bool = 0;
	data->disco = 0;
	data->img_data = mlx_get_data_addr(data->img_ptr, &(data->bpp),
			&(data->img_line), &(data->endian));
}

int	main(int argc, char **argv)
{
	t_data		*data;
	t_inst_obj	*insts;
	t_ref_obj	main_obj;

	data = NULL;
	if (argc != 2)
		error(0, data, NULL);
	if (!(data = (t_data*)malloc(sizeof(t_data))))
		go_away(data);
	inicializate_data(data);
	main_obj = make_ref_obj(argv[1], data);
	insts = make_obj_inst(&main_obj, 0.1f, 0.1f, 0.1f);
	data->obj_inst = insts;
	data->camera = initialize_camera(1);
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
