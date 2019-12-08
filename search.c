/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 15:20:10 by hyu               #+#    #+#             */
/*   Updated: 2019/12/07 16:55:42 by hyu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

char **make_map(node_point size)
{
	char **map;
	int		i;
	int		j;

	map = (char**)(malloc(sizeof(char*)*((int)size.y)));
	i = 0;
	//j = 0;
	while (i < (int)size.y)
	{
		j = 0;
		map[i] = (char*)malloc(((int)size.x + 1)*sizeof(char));
		while (j < (int)size.x)
		{
			map[i][j] = '.';
			j++;
		}
		map[i][(int)size.x] = '\0';
		i++;
	}
	return (map);
}

int		match(char **map, node_point size, node_point begin, t_point piece)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (begin.y + piece.y[i] >= size.y || begin.x + piece.x[i] >= size.x)
			return (-1);
		if (map[(int)begin.y + (int)piece.y[i]][(int)begin.x + (int)piece.x[i]] != '.')
            return (0);
		i++;
	}
	return (1);
}

void	write_map(char **map, node_point begin, t_point piece, int i)
{
	int j;

	j = 0;
	while (j < 4)
	{
		map[(int)begin.y + (int)piece.y[j]][(int)begin.x + (int)piece.x[j]] = 'A' + i;
		j++;
	}
}

void	ft_erase(char **map, node_point begin, node_point size, char c)
{
	if (begin.x < 0 || begin.y < 0)
		return;
	if (begin.x >= size.x || begin.y >= size.y)
		return;
	if (map[(int)begin.y][(int)begin.x] != c)
		return;

	map[(int)begin.y][(int)begin.x] = '.';
	ft_erase(map, (node_point){begin.x + 1, begin.y}, size, c);
	ft_erase(map, (node_point){begin.x - 1, begin.y}, size, c);
	ft_erase(map, (node_point){begin.x, begin.y + 1}, size, c);
	ft_erase(map, (node_point){begin.x, begin.y - 1}, size, c);
}

/*
void	search(char **map, node_point size, node_point begin, t_point *array, int i)
{
	if (begin.x < 0 || begin.y < 0)
	{
		return;
	}
	if (i >= size.num)
		return;
	if (begin.x >= size.x || begin.y >= size.y)
    {
		return;
	}
	if (map[(int)begin.y][(int)begin.x] != '.')
	{
		search(map, size, (node_point){begin.x + 1, begin.y}, array, i);
		search(map, size, (node_point){begin.x, begin.y + 1}, array, i);
	}
	if (map[(int)begin.y][(int)begin.x] == '.')
	{

		if (match(map, size, begin, array[i]) == 1)
		{
			write_map(map, begin, array[i], i);
			search(map, size, begin, array, i + 1);
		}
		else if (match(map, size, begin, array[i]) == 0)
		{
			search(map, size, (node_point){begin.x + 1, begin.y}, array, i);
			search(map, size, (node_point){begin.x, begin.y + 1}, array, i);
		}
	}
}

*/
/*void	ft_backtrack(char *map, int i, node_point begin, node_point size, char **array)
{
	ft_find_char(map, i - 1, begin, size);
	if (match(map, size, begin, array[i]) == 1)
		search(map, size, begin, array, i + 1);
	if (match(map, size, begin, array[i] == 0))
	{
		size.x += 1;
		size.y += 1;
		i = 0;
		search(map, size, begin, array, i);
	}
}
*/
void	ft_find_char(char **map, int i, node_point begin, node_point size, char c)
{
	if (begin.x < 0 || begin.y < 0)
		return;
	if (begin.x > size.x || begin.y > size.y)
		return;
	if (map[(int)begin.y][(int)begin.x] == c)
    {
		ft_putchar('e');
        ft_erase(map, begin, size,c);
        return;
    }
	ft_find_char(map, i, (node_point){begin.x + 1, begin.y}, size, c);
    ft_find_char(map, i, (node_point){begin.x - 1, begin.y}, size, c);
    ft_find_char(map, i, (node_point){begin.x, begin.y + 1}, size, c);
    ft_find_char(map, i, (node_point){begin.x, begin.y - 1}, size, c);
}

int		ft_backtrack(char **map, int i, node_point begin, node_point size, t_point *array)
{
	char c;

	c = 'A' + i;
	ft_find_char(map, i - 1, begin, size, c);
	if (match(map, size, begin, array[i]) == 1)
	{
		return (1);
	}
	if (match(map, size, begin, array[i]) == 0)
	{
		size.x += 1;
		size.y += 1;
		i = 0;
		return (0);
		//search(map, size, begin, array, i);
	}
	return (0);
}

void	find_empty(char **map, int i, node_point begin, node_point size, t_point *array)
{
}
void    search(char **map, node_point size, node_point begin, t_point *array, int i)
{
    if (begin.x < 0 || begin.y < 0 )
	   return;
 	if (i  >= size.num)
        return;
    if (begin.x >= size.x || begin.y >= size.y)
    {
		/*
		if (ft_backtrack(map, i, begin, size, array) == 1)
		{
			search(map, size, begin, array, i + 1);
		}
		if (ft_backtrack(map, i, begin, size, array) == 0)
		{
			size.x = size.x + 1;
			size.y = size.y + 1;
			i = 0;
			
			size.x += 1;
			size.y += 1;
			i = 0;*
			search(map, size, (node_point){0, 0}, array, 0);
		}
		*/
		return;
    }
    if (map[(int)begin.y][(int)begin.x] != '.')
    {
        search(map, size, (node_point){begin.x + 1, begin.y}, array, i);
        search(map, size, (node_point){begin.x, begin.y + 1}, array, i);
    }
    if (map[(int)begin.y][(int)begin.x] == '.')
    {

        if (match(map, size, begin, array[i]) == 1)
        {
            write_map(map, begin, array[i], i);
            search(map, size, begin, array, i + 1);
        }
        else if (match(map, size, begin, array[i]) == 0)
        {
            search(map, size, (node_point){begin.x + 1, begin.y}, array, i);
            search(map, size, (node_point){begin.x, begin.y + 1}, array, i);
        }
    }
}

int		main(void)
{
	int	i;
	node_point begin = {0, 0};
	t_point	*dummy;

	dummy = (t_point*)malloc(3*sizeof(t_point));
	i = 0;
	while (i < 4)
	{
		dummy[0].x[i] = 0;
		dummy[1].x[i] = 0;
		dummy[2].x[i] = 0;

		dummy[0].y[i] = i;
        dummy[1].y[i] = i;
        dummy[2].y[i] = i;
	//	dummy[3].y[i] = i;
		i++;
	}
	int	j;

	i = 0;
/*
	{
		j = 0;
		while (j < 4)
		{
			ft_putchar(dummy[i].x[j] + '0');
			ft_putchar(dummy[i].y[j] + '0');
			j++;
		}
		i++;
	}*/

	node_point size;

	size.x = 4;
	size.y = 4;
	size.num = 4;

	
	ft_putnbr(size.num);
//	size.num = 3;
	char **map;


	map = make_map(size);
	write_map(map, begin, dummy[0], 0);
	i = 0;
	while (i < 4)
	{
		printf("%s\n", map[i]);
		i++;
	}
	ft_find_char(map, i, begin, size, 'A');
	//ft_erase(map,begin, size, 0);
	//ft_putnbr(match(map, size, begin, dummy[0]));
	i = 0;
	while (i < 4)
	{
		printf("%s\n", map[i]);
		i++;
	}
	i = 0;
	search(map, size, begin, dummy, i);
	i = 0;
    while (i < 4)
    {
        printf("%s\n", map[i]);
        i++;
    }
	return (0);
}
