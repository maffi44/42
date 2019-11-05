/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 17:29:19 by mcamila           #+#    #+#             */
/*   Updated: 2019/11/05 14:39:57 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

typedef struct s_fill
{
	char order;
	int x_len;
	int y_len;
	char yx[4][4];
}            t_fill;

typedef struct		s_node
{
	int x;
}					t_node;

typedef struct		s_col
{
	struct s_col	*left;
	struct s_col	*right;
	t_node			*head;
	int				length;
	int				name;
}					t_col;

void	ft_apocalipse(void);

t_col	**ft_create_cols(int num)
{
	int		i;
	t_col	**cols;

	if (!(cols = (t_col**)malloc(sizeof((t_col*) * num))))
		ft_apocalipse();
	i = 0;
	while (i < num)
	{
		if (!(cols[i] = (t_col*)malloc(sizeof(t_col))))
			ft_apocalipse();
		cols[i]->head = NULL;
		cols[i]->length = 0;
		cols[i]->name = i + 1;
		if (i != 0)
		{
			cols[i - 1]->right = cols[i];
			cols[i]->left = cols[i - 1];
		}
		i++;
	}
	cols[num - 1]->right = cols[0];
	cols[0]->left = cols[num - 1];
	return cols;
}

int		ft_make_map(t_fill *figure, int tn)
{
	int ss; //length of square side
	int i;
	t_col	**cols;


	ss = 2;
	while (tn * 4 < ss * ss)
		ss++;
	i = 0;

	cols = ft_create_cols(ss);
	while (i < tn)
	{
		figure[i]
		i++;
	}
}

int					main(int argc, char **argv)
{
	t_fill				figure[26];
	unsigned long int	*rows;
	int					tn;
	int					fd;
	char				buf[BUFF_SIZE];

	fd = open(av[1], O_RDONLY);
	if (fd < 0 || ac != 2)
		exit(0);
	if ((tn = validity(fd, buf, figure) == 0)
	{
		//error
	}
	rows = ft_make_map(figure, tn);

}

typedef struct		s_Node
{
	struct s_Node	*right;
	struct s_Node	*down;
}					t_Node;

typedef struct	s_C_Header
{
	t_Node		*first;
}				t_C_Header;

typedef struct	s_R_Header
{
	t_Node		node[4];
}				t_R_Header;

typedef struct	s_T_Header
{
	t_R_Header	rows[121];
}				t_T_Header;

t_T_Header		tetrHeaders[26];
t_C_Header		ColHeaders[144];

void	ft_routineY(int i)
{

}