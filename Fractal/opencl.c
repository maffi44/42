/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 07:17:42 by mcamila           #+#    #+#             */
/*   Updated: 2020/03/05 14:14:11 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

t_opencl	*init_opencl(t_opencl *opencl)
{
	int fd;

	opencl = ft_memalloc(sizeof(t_opencl));
	opencl->ret = 0;
	fd = open("./kernel.cl", O_RDONLY);
	if (fd < 0)
		go_away(NULL);
	opencl->source_str = read_file(fd, &opencl->source_size);
	opencl->ret = clGetPlatformIDs(1, &opencl->pl_id,
			&opencl->ret_num_platforms);
	opencl->ret = clGetDeviceIDs(opencl->pl_id, CL_DEVICE_TYPE_GPU,
			1, &opencl->dev_id, &opencl->ret_num_devices);
	opencl->ctxt = clCreateContext(NULL, 1, &opencl->dev_id,
			NULL, NULL, &opencl->ret);
	opencl->cmd_queue = clCreateCommandQueue(opencl->ctxt,
			opencl->dev_id, 0, &opencl->ret);
	return (opencl);
}

int			cl_create_program(t_opencl *opencl)
{
	opencl->program = clCreateProgramWithSource(
			opencl->ctxt, 1, (const char **)&opencl->source_str,
			(const size_t *)&opencl->source_size, &opencl->ret);
	opencl->ret = clBuildProgram(opencl->program,
			1, &opencl->dev_id, NULL, NULL, NULL);
	opencl_debuger(opencl);
	opencl->kernel = clCreateKernel(opencl->program, "render", &opencl->ret);
	return (opencl->ret);
}

int			cl_init_params(t_opencl *opencl, t_data *data)
{
	opencl->data_size = HIEGHT * WIDTH;
	opencl->cl_data = clCreateBuffer(
			opencl->ctxt, CL_MEM_WRITE_ONLY,
			opencl->data_size * sizeof(cl_int), NULL, &opencl->ret);
	return (opencl->ret);
}

int			cl_run_kernel(t_opencl *opencl, t_data *data)
{
	size_t global_work_size[2];

	global_work_size[0] = WIDTH;
	global_work_size[1] = HIEGHT;
	opencl->ret = clSetKernelArg(opencl->kernel, 0,
			sizeof(cl_mem), (void *)&opencl->cl_data);
	opencl->ret = clSetKernelArg(opencl->kernel, 1,
			sizeof(t_params), (void *)&data->p);
	opencl->ret = clEnqueueNDRangeKernel(opencl->cmd_queue, opencl->kernel,
			2, NULL, global_work_size, NULL, 0, NULL, NULL);
	opencl->ret = clEnqueueReadBuffer(opencl->cmd_queue,
			opencl->cl_data, CL_TRUE, 0, opencl->data_size * sizeof(cl_int),
			data->img_data, 0, NULL, NULL);
	return (opencl->ret);
}
