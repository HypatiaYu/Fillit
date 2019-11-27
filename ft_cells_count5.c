/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cells_count5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:06:54 by hyu               #+#    #+#             */
/*   Updated: 2019/11/26 17:39:00 by hyu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
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

int     ***ft_coordinate_array(int  number_of_pieces)
{
    int i;
    int ***pieces_coordinates;

    i = 0;
    /* create enough space to hold all the spaces */
    pieces_coordinates = (int***)malloc((number_of_pieces) * sizeof(int**));
    /* malloc enough space for all the pieces */
    while (i < number_of_pieces)
    {
        pieces_coordinates[i] = (int**)malloc(2* sizeof(int*));
        pieces_coordinates[i][0] = (int*)malloc(4 * sizeof(int));
        pieces_coordinates[i][1] = (int*)malloc(4 * sizeof(int));
        i++;
    }
    return (pieces_coordinates);
}

void		ft_piece(char *sub_tilei, int **pieces_coordinate_arrayi)
{
	int i;
	int	y;
	int	x;
	int	k;

	y = 0;
	k = 0;
	while (i < 21)
	{
		if (sub_tilei[i] == '#')
		{
			x = i % 5;
			pieces_coordinate_arrayi[0][k] = x;
			pieces_coordinate_arrayi[1][k] = y;
			k++;
		}
		else if (sub_tilei[i] == '\n')
		{
			y++;
		}
		i++;
	}
	return ;
}

int		ft_tilenumber(char *tile)
{
	int	i;
	
	i = (ft_strlen(tile) + 1)/ 21;
	return (i);
}

int     ft_check_spaces(int ***piece_coordinate_array, int i)
{
    int j;
    int k;

    j = 0;

    /* check space against spaces before it*/
    while (j < i)
    {
        k = 0;
        /* check if each piece in set has the same coordinates*/
        while (piece_coordinate_array[i][0][k] != piece_coordinate_array[j][0][k] &&
                piece_coordinate_array[i][1][k] != piece_coordinate_array[j][1][k])
            k++;
        if (k == 4)
            j++;
        else
            return (0);
    }
    if (j == i)
        return (1);
    return (0);
}

void	assign_tiles(char *tile, int ***pieces_coordinate_array)
{
	int	i;
	int	j;
	char *subtile;

	i = 0;
	j = ft_tilenumber(tile);
	while (i < j)
	{
		subtile = ft_subtile(tile, i);
		printf("%s", subtile);
		ft_piece(subtile, pieces_coordinate_array[i]);
		free(subtile);
		i++;
	}
}

/*
int     ft_check_spaces(int ***piece_coordinate_array, int i)
{
    int j;
    int k;

    j = 0;

     check space against spaces before it
    while (j < i)
    {
        k = 0;
         check if each piece in set has the same coordinates
        while (piece_coordinate_array[i][0][k] != piece_coordinate_array[j][0][k] &&
                piece_coordinate_array[i][1][k] != piece_coordinate_array[j][1][k])
            k++;
        if (k == 4)
            j++;
        else
            return (0);
    }
    if (j == i)
        return (1);
    return (0);
}
*/

int     main(void)
{
	int	fd;
	char	*line;
	char	*tile;
	char 	*tmp;
	int		i;
	int		x;
	int		y;
	int		***pieces_coordinate;

	fd = open("input", O_RDONLY);
	//tile = (char**)malloc(4 * sizeof(char*));
	while (get_next_line(fd, &line) == 1)
	{
		if (tile == NULL)
			tile = ft_strnew(1);
		if (tile)
		{
			tile = ft_strjoin(tile, line);
			tile = ft_strjoin(tile, "\n");
		}
		i++;
	}
	//printf("%s", tile);

//	char	*sub_tile;
//	sub_tile = ft_subtile(tile, 1);
//	printf("%s", sub_tile);

//	int k;

//	k = ft_tilenumber(tile);
//	ft_putnbr(k);
	pieces_coordinate = ft_coordinate_array(4);
//	ft_piece(sub_tile, pieces_coordinate[1]);

	assign_tiles(tile, pieces_coordinate);
	int	l;
	l = 0;
	
	while (l < 4)
	{
		x = pieces_coordinate[1][0][l];
		y = pieces_coordinate[1][1][l];
		ft_putnbr(x);
		ft_putnbr(y);
		l++;
	}

	int	m;	
	m = ft_check_spaces(pieces_coordinate, 1);
	ft_putnbr(m);
//	assign_tiles(tile, pieces_coordinate);
	return (0);
}
