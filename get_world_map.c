/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_world_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 13:42:01 by rbozhko           #+#    #+#             */
/*   Updated: 2019/04/28 13:42:02 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdio.h>

int		**retrieve_maze(char *str)
{
	int		**maze;
	char	**tmp;
	int		k;
	int		i;
	int		j;

	i = 0;
	maze = (int **)malloc(sizeof(int *) * MAP_HEIGHT);
	tmp = ft_strsplit(str, '\n');
	while (tmp[i])
	{
		j = 0;
		k = 0;
		maze[i] = (int *)malloc(sizeof(int) * MAP_WIDTH);
		while (tmp[i][j] != '\0')
		{
			if (tmp[i][j] >= '0' && tmp[i][j] <= '9')
				maze[i][k++] = tmp[i][j] - '0';
			j++;
		}
		i++;
	}
	ft_free_bidarr(tmp, i);
	return (maze);
}

char	*read_from_file(int fd)
{
	char	*inf;
	char	*temp;
	char	*buffer;
	int		r;

	buffer = (char *)malloc(sizeof(char) * 9001);
	inf = (char *)malloc(sizeof(char));
	if ((r = read(fd, buffer, 0)) < 0)
	{
		ft_throw_exception("Passed argument couldn't be read");
	}
	while ((r = read(fd, buffer, 9000)) > 0)
	{
		buffer[r] = '\0';
		temp = inf;
		inf = ft_strjoin(inf, buffer);
		ft_strdel(&temp);
	}
	ft_strdel(&buffer);
	if (!ft_strlen(inf))
	{
		free(inf);
		inf = NULL;
	}
	return (inf);
}
