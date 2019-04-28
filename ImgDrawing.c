/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_to_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 13:41:53 by rbozhko           #+#    #+#             */
/*   Updated: 2019/04/28 13:41:54 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_pixel(t_main *main, int x, int y, int color)
{
	int r;
	int g;
	int b;

	r = color % 256;
	g = (color / 256) % 256;
	b = (color / 65536) % 256;
	main->data[((y * main->sline) + (x * 4))] = r;
	main->data[((y * main->sline) + (x * 4)) + 1] = g;
	main->data[((y * main->sline) + (x * 4)) + 2] = b;
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

void		draw_floor(t_main *main, double wall_x)
{
	if (main->side == 0 && R_DIR_X > 0)
	{
		main->floor_x_wall = main->map_x;
		main->floor_y_wall = main->map_y + wall_x;
	}
	else if (main->side == 0 && R_DIR_X < 0)
	{
		main->floor_x_wall = main->map_x + 1.0;
		main->floor_y_wall = main->map_y + wall_x;
	}
	else if (main->side == 1 && R_DIR_Y > 0)
	{
		main->floor_x_wall = main->map_x + wall_x;
		main->floor_y_wall = main->map_y;
	}
	else
	{
		main->floor_x_wall = main->map_x + wall_x;
		main->floor_y_wall = main->map_y + 1.0;
	}
	main->dist_wall = main->perp_wall_dist;
	main->dist_player = 0.0;
}