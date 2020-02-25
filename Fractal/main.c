/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:21:28 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/26 02:42:13 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		mouse_release(int button, int x, int y, t_data *data)
{
	x = y;
	if (button == 3)
	{
		((t_data *) data)->p.m_bool = 0;
		((t_data *) data)->p.sc_bool = 0;
	}
	ft_render(data);
	return (0);
}

int		mouse_move(int x0, int y0, t_data *data)
{
	int x;
	int y;

	data->p.k_re =(x0 - (float)WIDTH / 2) * 4 / WIDTH;
	data->p.k_im = (y0 - (float)HIEGHT / 2) * 4 / HIEGHT;
	if (((t_data*)data)->p.m_bool)
	{
		x = x0 - data->p.x;
		y = y0 - data->p.y;
		data->p.re_off -= (float)x * (4 * data->p.sc / WIDTH );
		data->p.im_off += (float)y * (4 * data->p.sc / HIEGHT);
		data->p.x = x0;
		data->p.y = y0;
	}
	ft_render(data);
	return (0);
}

void	inicializate_data(t_data *data)
{
	if (!(data->mlx_ptr = mlx_init()))
		go_away(data);
	if (!(data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HIEGHT, "fractal")))
		go_away(data);
	if (!(data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HIEGHT)))
		go_away(data);
	data->img_data = mlx_get_data_addr(data->img_ptr, &(data->p.bpp),
			&(data->p.img_line), &(data->p.endian));
	data->p.k_re = 0;
	data->p.k_im = 0;
	data->p.fract = 1;
	data->p.sc = 1;
	data->p.max_iteration = 25;
	data->p.re_off = 0;
	data->p.im_off = 0;
	data->p.m_bool = 0;
	data->p.sc_bool = 0;
	data->p.col.argb = 0x00FFFF00;
}

char		*read_file(int fd, size_t *size)
{
	char	*tmp;
	char	*res;
	ssize_t	num;
	char	buf[256];

	res = (char *)malloc(sizeof(char));
	res[0] = '\0';
	if (res < 0)
		return (NULL);
	while ((num = read(fd, buf, 255)) > 0)
	{
		buf[num] = '\0';
		tmp = res;
		res = ft_strjoin(res, buf);
		free(tmp);
	}
	if (size)
		*size = ft_strlen(res);
	return (res);
}

void pfn_notify (const char *errinfo, const void *private_info, size_t cb, void *user_data)
{
	ft_putendl(errinfo);
	ft_putendl((char*)private_info);
}
t_opencl * init_opencl(t_opencl * opencl)
{
	opencl = ft_memalloc(sizeof(t_opencl));
	opencl->ret = 0;
	int fd = open("./kernel.cl",  O_RDONLY);
	opencl->source_str = read_file(fd, &opencl->source_size);
	// /* получить доступные платформы */
	opencl->ret = clGetPlatformIDs(1, &opencl->pl_id, &opencl->ret_num_platforms);

	/* получить доступные устройства */
	opencl->ret = clGetDeviceIDs(opencl->pl_id, CL_DEVICE_TYPE_DEFAULT, 1, &opencl->dev_id, &opencl->ret_num_devices);

	// printf("device id ->%d  %d\n", opencl->dev_id, opencl->ret_num_devices);
	// /* создать контекст */
	opencl->ctxt = clCreateContext(NULL, 1, &opencl->dev_id, NULL, NULL, &opencl->ret);
	printf("-->%d", opencl->ret);

	// /* создаем команду */
	opencl->cmd_queue = clCreateCommandQueue(opencl->ctxt , opencl->dev_id, 0, &opencl->ret);
	printf("q-->%d", opencl->ret);
	return (opencl);
}



int cl_create_programm(t_opencl * opencl)
{

	opencl->program = clCreateProgramWithSource(opencl->ctxt, 1, (const char **)&opencl->source_str, (const size_t *)&opencl->source_size, &opencl->ret);
	printf("-->%d", opencl->ret);

	/* скомпилировать программу */
	opencl->ret = clBuildProgram(opencl->program, 1, &opencl->dev_id, NULL, NULL, NULL);


	char		buffer[1000];

	clGetProgramBuildInfo(opencl->program, opencl->dev_id, CL_PROGRAM_BUILD_LOG
			, 1000, buffer, NULL);
	write(1, buffer, ft_strlen(buffer));



	/* создать кернел */
	opencl->kernel = clCreateKernel(opencl->program, "test", &opencl->ret);
	return (opencl->ret);
}

int cl_init_params(t_opencl * opencl, t_data *data)
{
	opencl->data_size = HIEGHT * WIDTH;
	//opencl->res = (cl_int *)ft_memalloc(sizeof(cl_int) * opencl->data_size);
	opencl->cl_data = clCreateBuffer(opencl->ctxt, CL_MEM_READ_WRITE, opencl->data_size * sizeof(cl_int), NULL, &opencl->ret);
	return (opencl->ret);
}

int cl_run_kernel(t_opencl * opencl, t_data *data)
{
	size_t global_work_size[2] = {WIDTH,  HIEGHT};
	opencl->ret = clEnqueueWriteBuffer(opencl->cmd_queue, opencl->cl_data, CL_TRUE, 0, opencl->data_size * sizeof(cl_int), data->img_data , 0, NULL, NULL);

	opencl->ret = clSetKernelArg(opencl->kernel, 0, sizeof(cl_mem), (void *) &opencl->cl_data);
	opencl->ret = clSetKernelArg(opencl->kernel, 1, sizeof(t_params), (void *) &data->p);
	printf("--> arg%d\n", opencl->ret);

	opencl->ret = clEnqueueNDRangeKernel(opencl->cmd_queue, opencl->kernel, 2, NULL, global_work_size, NULL, 0, NULL, NULL);
	printf("-->dasdas%d\n", opencl->ret);
	opencl->ret = clEnqueueReadBuffer(opencl->cmd_queue, opencl->cl_data, CL_TRUE, 0, opencl->data_size * sizeof(cl_int), data->img_data , 0, NULL, NULL);
	printf("%d int:%lu\n", opencl->ret, opencl->data_size * sizeof(cl_int));

	// for (int i =0; i < 10; i++)
	// {
	// 	printf("%d \n", (data->img_data)[i]);
	// }
	return (opencl->ret);
}

int ft_render(t_data *data)
{
	ft_bzero(data->img_data, (WIDTH * HIEGHT) * sizeof(int));

	// for (int j = 0; j < data->height; j++)
	// {
	// 	for (int k = 0; k < data->width; k++)
	// 	{
	// 		ft_putpixel(data, k, j, (k / (data->width / 256 + 1)) << 16  | (j / (data->height / 256 + 1)) << 8) ;
	// 	}
	// }

	cl_run_kernel(data->opencl, data);
	data->p.col = color_loop(2, data->p.col);
	mlx_put_image_to_window (data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);

	return (0);
}
/*int main(void)
{
	t_opencl *opencl;
	data.width = 300;
	data.height = 300;
	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data.win_ptr = mlx_new_window(data.mlx_ptr, data.width, data.height, "Hello world")) == NULL)
		return (EXIT_FAILURE);
	data.img_ptr =  mlx_new_image(data.mlx_ptr, data.width , data.height);
	data.img_data = mlx_get_data_addr(data.img_ptr, &data.bpp, &data.size_line, &data.endian);
	opencl = init_opencl(opencl);
	ft_putstr(opencl->source_str);

	cl_create_programm(opencl);
	cl_init_params(opencl, &data);
	ft_render(&data, opencl);
	mlx_key_hook(data.win_ptr, ft_press, &data);
	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
}*/

inline void	put_pixel(int x, int y, int color, t_data *data)
{
	if (x >= WIDTH || x < 0 || y >= HIEGHT || y < 0)
		return ;
	((int*)(data->img_data))[x + (y * WIDTH)] = color;
}

int		main(int argc, char **argv)
{
	t_data		*data;



	data = NULL;
//	if (argc != 2)
//		error(0, data, NULL);
	if (!(data = (t_data*)malloc(sizeof(t_data))))
		go_away(data);
	inicializate_data(data);



	data->opencl = init_opencl(data->opencl);

	cl_create_programm(data->opencl);
	cl_init_params(data->opencl, data);

	ft_render(data);
	mlx_mouse_hook(data->win_ptr, mouse_press, (void*)data);
	mlx_hook(data->win_ptr, 2, 0, key_press, (void*)data);
	mlx_hook(data->win_ptr, 3, 0, key_release, (void*)data);
	mlx_hook(data->win_ptr, 4, 0, mouse_press, (void*)data);
	mlx_hook(data->win_ptr, 5, 0, mouse_release, (void*)data);
	mlx_hook(data->win_ptr, 6, 0, mouse_move, (void*)data);
	mlx_hook(data->win_ptr, 17, 0, x_press, data);
	mlx_loop_hook(data->mlx_ptr, ft_render, (void*)data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
