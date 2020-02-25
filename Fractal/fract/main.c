#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include "libft.h"
# define CL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif 

typedef struct    data_s
{
	void        *mlx_ptr;
	void        *win_ptr;
	void  		*img_ptr;
	char 		*img_data;
	int width;
	int height;
	int bpp;
	int size_line;
	int endian;
}                 data_t;

typedef struct opencl_s
{
	int ret;
	cl_platform_id		pl_id;
	cl_device_id		dev_id;
	cl_context			ctxt;
	cl_command_queue	cmd_queue;
	cl_program program;
	cl_kernel kernel;
	cl_uint ret_num_platforms;
	cl_uint ret_num_devices;
	char * source_str;
	size_t source_size;
	cl_mem cl_data;
	size_t data_size;
	cl_int *res;
} t_opencl;



int k = 0;
int j = 0;
data_t 	data;


void ft_putpixel(data_t *data,int x, int y, int color)
{
	((int*)data->img_data)[x + y * data->width] = color;

}


int ft_press(int key, void *data_void)
{

	
	return (0);
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
	ft_putstr(opencl->source_str);

	return (opencl);
}



int cl_create_programm(t_opencl * opencl)
{	
	printf("s--->%s\n", opencl->source_str);

	opencl->program = clCreateProgramWithSource(opencl->ctxt, 1, (const char **)&opencl->source_str, (const size_t *)&opencl->source_size, &opencl->ret);
	printf("-->%d", opencl->ret);

	/* скомпилировать программу */
	opencl->ret = clBuildProgram(opencl->program, 1, &opencl->dev_id, NULL, NULL, NULL);
	/* создать кернел */
	opencl->kernel = clCreateKernel(opencl->program, "test", &opencl->ret);
	return (opencl->ret);
}

int cl_init_params(t_opencl * opencl, data_t *data)
{
	opencl->data_size = data->height * data->width;
	//opencl->res = (cl_int *)ft_memalloc(sizeof(cl_int) * opencl->data_size);
	opencl->cl_data = clCreateBuffer(opencl->ctxt, CL_MEM_READ_WRITE, opencl->data_size * sizeof(cl_int), NULL, &opencl->ret);
	opencl->ret = clEnqueueWriteBuffer(opencl->cmd_queue, opencl->cl_data, CL_TRUE, 0, opencl->data_size * sizeof(cl_int), data->img_data , 0, NULL, NULL);
	return (opencl->ret);
}

int cl_run_kernel(t_opencl * opencl, data_t *data)
{
	size_t global_work_size[1] = { opencl->data_size };
	opencl->ret = clSetKernelArg(opencl->kernel, 0, sizeof(cl_mem), (void *) &opencl->cl_data);	

	opencl->ret = clEnqueueNDRangeKernel(opencl->cmd_queue, opencl->kernel, 1, NULL, global_work_size, NULL, 0, NULL, NULL);
	printf("-->dasdas%d\n", opencl->ret);
	opencl->ret = clEnqueueReadBuffer(opencl->cmd_queue, opencl->cl_data, CL_TRUE, 0, opencl->data_size * sizeof(cl_int), data->img_data , 0, NULL, NULL);
	printf("%d int:%lu\n", opencl->ret, opencl->data_size * sizeof(cl_int));

	// for (int i =0; i < 10; i++)
	// {
	// 	printf("%d \n", (data->img_data)[i]);
	// }
	return (opencl->ret);	
}

void ft_render(data_t *data, t_opencl *opencl)
{
	

	// for (int j = 0; j < data->height; j++)
	// {
	// 	for (int k = 0; k < data->width; k++)
	// 	{
	// 		ft_putpixel(data, k, j, (k / (data->width / 256 + 1)) << 16  | (j / (data->height / 256 + 1)) << 8) ;
	// 	}
	// }

	 cl_run_kernel(opencl, data);

	mlx_put_image_to_window (data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
}
int main(void)
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
}
