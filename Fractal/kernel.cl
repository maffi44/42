#define WIDTH 2000
#define HIEGHT 2000

typedef union		u_color
{
	unsigned int	argb;
	unsigned char	colors[4];
}					t_color;

typedef struct 	s_params
{
	int			img_line;
	int			bpp;
	int			endian;
	int			x;
	int			y;
	float		k_re;
	float 		k_im;
	int 		fract;
	float	 	sc;
	int 		max_iteration;
	float 		re_off;
	float 		im_off;
	int			m_bool;
	int 		sc_bool;
	t_color		col;
	int 		jul_bool;
}				t_params;

typedef struct	s_complex
{
	float		re;
	float		im;
}				t_complex;

t_complex	init_complex(float re, float im);
t_complex	julia(t_complex z, t_complex c);
t_complex	mandelbar_2(t_complex z, t_complex c);
t_complex	mandelbar(t_complex z, t_complex c);
int			fractol_frame(t_params *params, int x, int y);
t_complex	f1(t_complex z, t_complex c);
t_complex	f2(t_complex z, t_complex c);
t_complex	f3(t_complex z, t_complex c);
t_complex	f4(t_complex z, t_complex c);
float 		f_abs(float f);

float 		f_abs(float f)
{
	if (f < 0)
		return (f * -1);
	return (f);
}

t_complex	init_complex(float re, float im)
{
	t_complex c;

	c.re = re;
	c.im = im;
	return (c);
}

t_complex	julia(t_complex z, t_complex c)
{
	z = init_complex(z.re * z.re - z.im * z.im + c.re,
					 2.0f * z.re * z.im + c.im);
	return (z);
}

t_complex	mandelbar_2(t_complex z, t_complex c)
{
	z = init_complex(z.re * z.re - z.im * z.im + c.re,
			-2.0f * z.re * z.im + c.im);
	return (z);
}

t_complex	mandelbar(t_complex z, t_complex c)
{
	z = init_complex(z.re * z.re - z.im * z.im + c.re,
					 2.0f * z.re * z.im + c.im);
	return (z);
}

t_complex	f1(t_complex z, t_complex c)
{
	z = init_complex(z.re * z.re - z.im * z.im + c.re,
					 f_abs(2.0f * z.re * z.im + c.im));
	return (z);
}

t_complex	f2(t_complex z, t_complex c)
{
	z = init_complex(f_abs(z.re * z.re - z.im * z.im + c.re),
					 f_abs(2.0f * z.re * z.im + c.im));
	return (z);
}

t_complex	f3(t_complex z, t_complex c)
{
	z = init_complex(f_abs(z.re * z.re - z.im * z.im + c.re),
					 (2.0f * z.re * z.im + c.im));
	return (z);
}

t_complex	f4(t_complex z, t_complex c)
{
	z = init_complex((z.re * z.re - z.im * z.im + c.re),
					 (4.0f * z.re * z.im + c.im));
	return (z);
}

int	fractol_frame(t_params *params, int x, int y)
{
	int max_iteration;
	int iteration;
	t_complex min;
	t_complex max;
	t_complex f;
	t_complex c;
	t_complex z;
	t_color col;
	t_complex k;

	min = init_complex(-2 * params->sc + params->re_off, -2 * params->sc + params->im_off);
	max = init_complex(2 * params->sc + params->re_off, 2 * params->sc + params->im_off);
	f = init_complex((max.re - min.re) / (get_global_size(0)  - 1),
			(max.im - min.im) / (get_global_size(1)  - 1));
	max_iteration = params->max_iteration;
	col.argb = 0;
	k = init_complex(params->k_re, params->k_im);

    c.im = max.im - y * f.im;

    c.re = min.re + x * f.re;
    z = init_complex(c.re, c.im);
    iteration = 0;
    while((z.re * z.re + z.im * z.im <= 4)
        && (iteration < max_iteration))
    {
        if (params->fract == 0)
            z = mandelbar(z, c);
        else if (params->fract == 1)
            z = mandelbar_2(z, c);
        else if (params->fract == 2)
            z = julia(z, k);
		else if (params->fract == 3)
			z = f1(z, c);
		else if (params->fract == 4)
			z = f2(z, k);
		else if (params->fract == 5)
			z = f3(z, c);
		else
			z = f4(z, c);
        iteration++;
    }
    col.colors[0] = params->col.colors[0] * (float)iteration / max_iteration;
    col.colors[1] = params->col.colors[1] * (float)iteration / max_iteration;
    col.colors[2] = params->col.colors[2] * (float)iteration / max_iteration;
    if (iteration == max_iteration)
        col.argb = 0;
	return col.argb;
}



__kernel void render(__global int* img, t_params params)
{
	int x = get_global_id(0);
	int y = get_global_id(1);

	img[x + y * get_global_size(0) ] = fractol_frame(&params, x, y);
}