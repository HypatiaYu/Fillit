/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:44:34 by hyu               #+#    #+#             */
/*   Updated: 2019/12/07 13:06:48 by hyu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"

int		get_next_line(const int fd, char **line);

# define BUFF_SIZE 32
# define MAX_FD 1024 + 1

typedef struct s_point{
	int		ID;
	int		x[4];
	int		y[4];
}				t_point;


typedef struct node
{
	int			x;
	int			y;
	int			num;
}				node_point;

#endif
