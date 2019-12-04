/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 13:44:24 by hyu               #+#    #+#             */
/*   Updated: 2019/12/04 13:56:17 by hyu              ###   ########.fr       */
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

int		character_counter(char *s_input, char c, int n)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (i < 21)
	{
		if (s_input[i] == c)
			counter++;
		i++;
	}
	if (counter == n)
		return (1);
	return (0);
}

int		check_input(char *s_input)
{
	if (s_input[0] == '\n')
		return (0);
	if (character_counter(s_input, '.', 12) == 0)
		return (0);
	if (character_counter(s_input, '#', 4) == 0)
		return (0);
	if (character_counter(s_input, '\n', 5) == 0)
		return (0);
	return (1);
}

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
	ft_putnbr(check_input(subtile));
	return (0);
}
