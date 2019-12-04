/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cells_count6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 19:18:40 by hyu               #+#    #+#             */
/*   Updated: 2019/12/04 13:25:55 by hyu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

char	*ft_subtile(char *tile, int	piece)
{
	char	*sub_tile;
	int		i;

	sub_tile = (char*)malloc(21*sizeof(char));
	i = 0;
	while (i < 21)
	{
		sub_tile[i] = tile[i + 21 * piece];
		i++;
	}
	sub_tile[i] = '\0';
	return (sub_tile);
}

int		ft_numberpieces(char *tile)
{
	int	i;
	
	i = (ft_strlen(tile) + 1)/ 21;
	return (i);
}

int		compare_struct(t_point s1, t_point s2)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (s1.x[i] == s2.x[i] && s1.y[i] == s2.y[i])
			i++;
		else
			return (0);
	}
	return (1);
}

t_point		ft_piece(char *sub_tilei, t_point array)
{
	int i;
	int	y_coord;
	int	x_coord;
	int	k;

	y_coord = 0;
	k = 0;
	i = 0;
	while (i < 21)
	{
		if (sub_tilei[i] == '#')
		{
			x_coord = i % 5;
			ft_putnbr(x_coord);
			ft_putnbr(y_coord);
			array.x[k] = x_coord;
			array.y[k] = y_coord;
			k++;
		}
		else if (sub_tilei[i] == '\n')
		{
			y_coord++;
		}
		i++;
	}
	return (array);
}

t_point     *ft_coordinate_array(char *tile)
{
	int		i;
    int     num_pieces;
	char 	*subtile;
    t_point *struct_list;
	t_point	coord;

    num_pieces = ft_numberpieces(tile);
	i = 0;
    struct_list = (t_point*)malloc(num_pieces * sizeof(t_point));
	while (i < num_pieces)
	{
		subtile = ft_subtile(tile, i);
		coord = ft_piece(subtile, coord);
		struct_list[i] = coord;
		i++;
	}
	return (struct_list);
}

int		ft_x_minormax(t_point s1, int i)
{
	int	retval;
	int k;

	k = 0;
	retval = s1.x[i];
	/* find the max*/
	if (i == 1)
	{
		retval = 
	}


}

#include <stdlib.h>
#include <stdio.h>

int     main(void)
{
	int	fd;
	char *line;
	char *tile;
	char *tmp;
	char *subtile;

	fd = open("input", O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		if (tile == NULL)
			tile = ft_strnew(1);
		if (tile)
		{
			tile = ft_strjoin(tile, line);
			tile = ft_strjoin(tile, "\n");
		}
	}
	t_point s1;

	subtile = ft_subtile(tile, 0);
	printf("%s\n", subtile);
	s1 = ft_piece(subtile, s1);

	int	i;
	i = 0;
	ft_putchar('\n');
   	while (i < 4)
	{
		ft_putnbr(s1.x[i]);
		ft_putnbr(s1.y[i]);
		ft_putchar('\n');
		i++;
	}
	ft_coordinate_array(tile);
	return (0);
}
