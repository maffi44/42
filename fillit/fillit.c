/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 13:24:06 by mcamila           #+#    #+#             */
/*   Updated: 2019/10/21 15:14:42 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

void ft_usage(void)
{

}

void ft_make(char *s)
{

}

int	ft_check_arg(char *arg)
{
	return (0);
	ft_make_hui(arg);
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_usage();
		return (0);
	}
	if (!(ft_check_arg(argv[1])))
	{
		ft_putendl("error");
		return (0);
	}

}