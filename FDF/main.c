/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:21:28 by mcamila           #+#    #+#             */
/*   Updated: 2020/01/25 12:51:14 by mcamila          ###   ########.fr       */
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

int expose(void *data)
{
//	if (((t_data*)data)->mouse_bool)
//		mlx_pixel_put(((t_data*)data)->mlx_ptr, ((t_data*)data)->win_ptr, ((t_data*)data)->x, ((t_data*)data)->y, 0x00FFFFFF);
	return (0);
}

int	key_press(int key, void *data)
{
	if (key == 53)
		go_away(data);
	return (0);
}

int	key_release(int key, void *param)
{
	return (0);
}

int mouse_press(int button, int x, int y, void *data)
{
	if (button == 1)
	{
		if (((t_data *) data)->mouse_bool == 0) {
			((t_data *) data)->mouse_bool = 1;
			((t_data *) data)->x = x;
			((t_data *) data)->y = y;
		}
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
					0.5f,
					x,
					y,
					1.0f,
					data
					);
		}
	}
	return (0);
}

int	mouse_release(int button, int x, int y, void *data)
{
//	if (button == 1)
//		((t_data *) data)->mouse_bool = 0;
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
//	if (((t_data*)data)->mouse_bool)
//	{
//		draw_line(x, y, ((t_data*)data)->x, ((t_data*)data)->y, data);
//		((t_data*)data)->x = x;
//		((t_data*)data)->y = y;
//	}
	return (0);
}

int	x_press(void *data)
{
	go_away(data);
	return (0);
}

int	main() {
	t_data	*data;

	if (!(data = (t_data*)malloc(sizeof(t_data))))
		go_away(data);
	if (!(data->mlx_ptr = mlx_init()))
		go_away(data);
	if (!(data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HIEGHT, "FDF")))
		go_away(data);
	data->mouse_bool = 0;

	t_ref_obj obj;

	obj.pt = (t_pt3*)malloc(sizeof(t_pt3) * 8);
	obj.tri = (t_tri*)malloc(sizeof(t_tri) * 12);
	obj.num_of_pts = 8;
	obj.num_of_tris = 12;

	obj.pt[0].x = -2;
	obj.pt[0].y = -2;
	obj.pt[0].z = -2;

	obj.pt[1].x = -2;
	obj.pt[1].y = 2;
	obj.pt[1].z = -2;

	obj.pt[2].x = 2;
	obj.pt[2].y = 2;
	obj.pt[2].z = -2;

	obj.pt[3].x = 2;
	obj.pt[3].y = -2;
	obj.pt[3].z = -2;

	obj.pt[4].x = -2;
	obj.pt[4].y = -2;
	obj.pt[4].z = 2;

	obj.pt[5].x = -2;
	obj.pt[5].y = 2;
	obj.pt[5].z = 2;

	obj.pt[6].x = 2;
	obj.pt[6].y = 2;
	obj.pt[6].z = 2;

	obj.pt[7].x = 2;
	obj.pt[7].y = -2;
	obj.pt[7].z = 2;

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
	obj.tri[5].pt[1] = 4;
	obj.tri[5].pt[2] = 5;

	obj.tri[6].pt[0] = 5;
	obj.tri[6].pt[1] = 4;
	obj.tri[6].pt[2] = 1;

	obj.tri[7].pt[0] = 1;
	obj.tri[7].pt[1] = 4;
	obj.tri[7].pt[2] = 0;

	obj.tri[8].pt[0] = 1;
	obj.tri[8].pt[1] = 2;
	obj.tri[8].pt[2] = 5;

	obj.tri[9].pt[0] = 5;
	obj.tri[9].pt[1] = 2;
	obj.tri[9].pt[2] = 6;

	obj.tri[10].pt[0] = 0;
	obj.tri[10].pt[1] = 3;
	obj.tri[10].pt[2] = 4;

	obj.tri[11].pt[0] = 3;
	obj.tri[11].pt[1] = 4;
	obj.tri[11].pt[2] = 7;

	data->obj_refs = &obj;

	t_inst_obj	*insts;
	insts = (t_inst_obj*)malloc(sizeof(t_inst_obj) * 2);
	insts[0].ref = &obj;
	insts[0].translate.x = -1;
	insts[0].translate.y = 0;
	insts[0].translate.z = 4;

	insts[1].ref = &obj;
	insts[1].translate.x = 5;
	insts[1].translate.y = 0;
	insts[1].translate.z = 5;

	render_frame(insts, 2, data);

	mlx_hook(data->win_ptr, 2, 0, key_press, data);
	mlx_hook(data->win_ptr, 3, 0, key_release, (void*)0);
	mlx_hook(data->win_ptr, 4, 0, mouse_press, data);
	mlx_hook(data->win_ptr, 5, 0, mouse_release, data);
	mlx_hook(data->win_ptr, 6, 0, mouse_move, data);
	mlx_hook(data->win_ptr, 12, 0, expose, data);
	mlx_hook(data->win_ptr, 17, 0, x_press, data);

	mlx_loop(data->mlx_ptr);
	return (0);
}
