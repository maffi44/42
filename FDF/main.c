/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:21:28 by mcamila           #+#    #+#             */
/*   Updated: 2020/01/18 16:33:55 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void swap(int* a , int*b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

// returns absolute value of number
float absolute(float x )
{
	if (x < 0) return -x;
	else return x;
}

//returns integer part of a floating point number
int iPartOfNumber(float x)
{
	return (int)x;
}

//rounds off a number
int roundNumber(float x)
{
	return iPartOfNumber(x + 0.5) ;
}

//returns fractional part of a number
float fPartOfNumber(float x)
{
	if (x>0) return x - iPartOfNumber(x);
	else return x - (iPartOfNumber(x)+1);

}

//returns 1 - fractional part of number
float rfPartOfNumber(float x)
{
	return 1 - fPartOfNumber(x);
}

// draws a pixel on screen of given brightness
// 0<=brightness<=1. We can use your own library
// to draw on screen
void drawPixel( int x , int y , float brightness, t_data *data)
{
	int b = 255 * (1 - brightness);
	int c = b;
	c <<= 8;
	c += b;
	c <<= 8;
	c += b;
	mlx_pixel_put((data)->mlx_ptr, (data)->win_ptr, x, y, c);
//	SDL_SetRenderDrawColor(pRenderer, c, c, c, 255);
//	SDL_RenderDrawPoint(pRenderer, x, y);
}

void	draw_line(int x0, int y0, int x1, int y1, t_data *data)
{
	int steep = absolute(y1 - y0) > absolute(x1 - x0) ;

	// swap the co-ordinates if slope > 1 or we
	// draw backwards
	if (steep)
	{
		swap(&x0 , &y0);
		swap(&x1 , &y1);
	}
	if (x0 > x1)
	{
		swap(&x0 ,&x1);
		swap(&y0 ,&y1);
	}

	//compute the slope
	float dx = x1-x0;
	float dy = y1-y0;
	float gradient = dy/dx;
	if (dx == 0.0)
		gradient = 1;

	int xpxl1 = x0;
	int xpxl2 = x1;
	float intersectY = y0;

	// main loop
	if (steep)
	{
		int x;
		for (x = xpxl1 ; x <=xpxl2 ; x++)
		{
			// pixel coverage is determined by fractional
			// part of y co-ordinate
			drawPixel(iPartOfNumber(intersectY), x,
					  rfPartOfNumber(intersectY), data);
			drawPixel(iPartOfNumber(intersectY)-1, x,
					  fPartOfNumber(intersectY), data);
			intersectY += gradient;
		}
	}
	else
	{
		int x;
		for (x = xpxl1 ; x <=xpxl2 ; x++)
		{
			// pixel coverage is determined by fractional
			// part of y co-ordinate
			drawPixel(x, iPartOfNumber(intersectY),
					  rfPartOfNumber(intersectY), data);
			drawPixel(x, iPartOfNumber(intersectY)-1,
					  fPartOfNumber(intersectY), data);
			intersectY += gradient;
		}
	}
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
		((t_data *) data)->mouse_bool = 1;
		((t_data*)data)->x = x;
		((t_data*)data)->y = y;
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
		draw_line(x, y, ((t_data*)data)->x, ((t_data*)data)->y, data);
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

	if (!(data = (t_data*)malloc(sizeof(t_data))))
		go_away(data);
	if (!(data->mlx_ptr = mlx_init()))
		go_away(data);
	if (!(data->win_ptr = mlx_new_window(data->mlx_ptr, 1920, 1080, "rissovalka")))
		go_away(data);
	data->mouse_bool = 0;

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
