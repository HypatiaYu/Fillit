/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 16:28:11 by hyu               #+#    #+#             */
/*   Updated: 2019/12/08 17:31:21 by hyu              ###   ########.fr       */
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
    int     i;
    int     j;
    
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

int     match(char **map, node_point size, node_point begin, t_point piece)
{
    int i;

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

void    write_map(char **map, node_point begin, t_point piece, int i)
{
    int j;

    j = 0;
    while (j < 4)
    {
        map[(int)begin.y + (int)piece.y[j]][(int)begin.x + (int)piece.x[j]] = 'A' + i;
        j++;
    }
}

node_point  unassigned_empty(char **map, node_point size, t_point *array, int i, node_point origin)
{
    while (origin.y < size.y)
    {
		while (origin.x < size.x)
        {
            if (map[(int)origin.y][(int)origin.x] == '.' && match(map, size, origin, array[i]) == 1)
                return (origin);
            origin.x = origin.x + 1;
        }
        origin.y = origin.y + 1;
		origin.x = 0;
    }
    return (origin);
}

node_point  next_empty(char **map, node_point size, t_point *array, int i, node_point origin)
{
    if (origin.x < size.x)
        origin.x = origin.x + 1;
    if (origin.x == size.x)
	{
        origin.x = 0;
        origin.y = 1 + origin.y;
    }
    origin = unassigned_empty(map, size, array, i, origin);
    return (origin);
}

void    ft_erase(char **map, node_point begin, node_point size, char c)
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

void    ft_find_char(char **map, int i, node_point origin, node_point size, char c)
{
	//ft_putchar('d');
    if (origin.x < 0 || origin.y < 0)
        return;
	//ft_putchar('d');
    if (origin.x >= size.x || origin.y >= size.y)
        return;
    if (map[(int)origin.y][(int)origin.x] == c)
    {
        ft_putchar('e');
        ft_erase(map, origin, size, c);        
    }

    ft_find_char(map, i, (node_point){origin.x + 1, origin.y}, size, c);
    //ft_find_char(map, i, (node_point){begin.x - 1, begin.y}, size, c);
    ft_find_char(map, i, (node_point){origin.x, origin.y + 1}, size, c);
    //ft_find_char(map, i, (node_point){begin.x, begin.y - 1}, size, c);
}

/*
void    ft_erase(char **map, node_point begin, node_point size, char c)
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
*/
int     ft_backtrack(char **map, int i, node_point begin, node_point size, t_point *array)
{
	ft_putchar('a');
	node_point origin = {0, 0};
    char c;

    c = 'A' + i - 1;
	ft_putchar('b');
    ft_find_char(map, i - 1, origin, size, c);
	ft_putchar('c');
	origin = unassigned_empty(map, size, array, i - 1, origin);
	origin = next_empty(map, size, array, i - 1, origin);
	write_map(map, begin, array[i - 1], i - 1);
	origin = unassigned_empty(map, size, array, i, origin);
	write_map(map, origin, array[i], i);
	/*
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
    }*/
    return (0);
}

void    search(char **map, node_point size, node_point begin, t_point *array, int i)
{
    if (begin.x < 0 || begin.y < 0 )
       return;
    if (i  >= size.num)
        return;
    if (begin.x >= size.x || begin.y >= size.y)
    {
		ft_backtrack(map, i, begin, size, array);
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
int     main(void)
{
    int i;
    node_point begin = {0, 0};
    t_point *dummy;

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
        i++;
    }
	char **map;
	node_point size;

    size.x = 4;
    size.y = 4;
    size.num = 4;
	map = make_map(size);
	i = 0;
    while (i < 4)
    {
        printf("%s\n", map[i]);
        i++;
    }
	i = 0;
	search(map, size, begin, dummy, i);
	//ft_backtrack(char **map, int i, node_point begin, node_point size, t_point *array)
    //write_map(map, begin, dummy[0], 0);
	/*
	write_map(map, begin, dummy[1], 1);
	write_map(map, begin, dummy[2], 2);*/
	/*
	i = 0;
    while (i < 4)
    {
        printf("%s\n", map[i]);
        i++;
    }
	node_point origin = {0, 0};
	i = 1;
	origin = unassigned_empty(map, size, dummy, i, origin);
	write_map(map, origin, dummy[1], 1);
	i = 0;
	while (i < 4)
	{
		printf("%s\n", map[i]);
		i++;
	}
	i = 2;
	origin = next_empty(map, size, dummy, i, origin);
	write_map(map, origin, dummy[2], 2);
	i = 0;
	while (i < 4)
	{
		printf("%s\n", map[i]);
		i++;
	}
	i = 2;
	begin.x = 2;
	begin.y = 0;
	ft_backtrack(map, i, begin, size, dummy);
	i = 0;
	while (i < 4)
	{
		printf("%s\n", map[i]);
		i++;
	}*/
	/*
	ft_putnbr(origin.x);
	ft_putchar('\n');
	ft_putnbr(origin.y);
	ft_putchar('\n');
	origin = next_empty(map, size, dummy, i, origin);
	ft_putnbr(origin.x);
    ft_putchar('\n');
	ft_putnbr(origin.y);*/
	return (0);
}
