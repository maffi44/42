/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 16:43:28 by mcamila           #+#    #+#             */
/*   Updated: 2020/01/19 20:09:58 by mcamila          ###   ########.fr       */
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
/*
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
*/
/*
void draw_line(int x0, int y0, int x1, int y1, t_data *data)
{
	double x;
	double y;
	double a;
	double b;


//	if (y0 > y1)
//	{
//		swap(&x0 ,&x1);
//		swap(&y0 ,&y1);
//	}
	int dy = y1 - y0;
	int dx = x1 - x0;
	if (absolute(dx) > absolute(dy))
	{
		if (x0 > x1)
		{
			swap(&x0 ,&x1);
			swap(&y0 ,&y1);
		}
		a = dy/dx;
		y = y0;
		x = x0;
		while (x <= x1)
		{
			mlx_pixel_put((data)->mlx_ptr, (data)->win_ptr, x, y, 0x00FFFFFF);
			y = (y + a);
			x++;
		}
	} else
	{
		if (y0 > y1)
		{
			swap(&x0 ,&x1);
			swap(&y0 ,&y1);
		}
		a = dx/dy;
		y = y0;
		x = x0;
		while (y <= y1)
		{
			mlx_pixel_put((data)->mlx_ptr, (data)->win_ptr, x, y, 0x00FFFFFF);
			x = (x + a);
			y++;
		}
	}
	if ()
//	if (dx == 0)
//		a = 1;
//	else
//		a = dy/dx;
	a = dy/dx;
//	a = (double)(y1 - y0)/(double)(x1 - x0);
//	b = y0 - (a * x0);
	x = x0;
	y = y0;
//	printf("%f", a);
	while (x <= x1)
	{
		mlx_pixel_put((data)->mlx_ptr, (data)->win_ptr, x, y, 0x00FFFFFF);
		y = (int)(y + a);
		//drawPixel(x, y, 1, data);
		x++;
	}
}
*/

void	draw_line (int x0, int y0, int x1, int y1, t_data *data, int color)
{
	int dx;
	int dy;

	if (x0 == x1 && y0 == y1)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x0, y0, color);
		return;
	}
	if (absolute(x0 - x1) > absolute(y0 - y1)) {
		if (x0 > x1) {
			swap(&x0, &x1);
			swap(&y0, &y1);
		}

		dx = x0 - x1;
		dy = y0 - y1;

		double a;

		a = (double) dy / (double) dx;
		double x;
		double y;
		x = x0;
		y = y0;
		while (x <= x1) {
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, (int) x, (int) y, color);
			y += a;
			x++;
		}
	} else
	{
		if (y0 > y1) {
			swap(&x0, &x1);
			swap(&y0, &y1);
		}

		dx = x0 - x1;
		dy = y0 - y1;

		double a;

		a = (double) dx / (double) dy;
		double x;
		double y;
		x = x0;
		y = y0;
		while (y <= y1) {
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, (int) x, (int) y, color);
			x += a;
			y++;
		}
	}
}


void draw_tri(int x0, int y0, int x1, int y1, int x2, int y2, t_data *data) {
	if (y0 > y1)
	{
		swap(&y1, &y0);
		swap(&x1, &x0);
	}
	if (y0 > y2)
	{
		swap(&y2, &y0);
		swap(&x2, &x0);
	}
	if (y1 > y2)
	{
		swap(&y1, &y2);
		swap(&x1, &x2);
	}

	int y = y0;
	double a1 = absolute(x0 - x1) / (y1 - y0);
	double a2 = absolute(x0 - x2) / (y2 - y0);
	int b1 = absolute(x1 - x0);
	int b2 = absolute(x0 - x2);
	while (y <= y1)
	{
		draw_line(a1 * y, y, a2 * y, y, data, 0xAAFFFFFF);
		y++;
	}
	a1 = absolute(x2 - x1) / (y2 - y1);
	b1 = x2 - x1;
	while (y <= y2)
	{
		draw_line(a1 * y + b1, y, a2 * y, y, data, 0xAAFFFFFF);
		y++;
	}

	draw_line(x0,y0,x1,y1,data,0x00FFFFFF);
	draw_line(x2,y2,x1,y1,data,0x00FFFFFF);
	draw_line(x0,y0,x2,y2,data,0x00FFFFFF);
}
