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

void	draw_line(int x, t_main *main)
{
	int y;
	int d;
	int tex_y;

	y = main->draw_start;
	while (y < main->draw_end)
	{
		d = y * 256 - HEIGHT * 128 + main->line_height * 128;
		tex_y = ((d * TEX_HEIGHT) / main->line_height) / 256;
		main->color = main->textures[main->tex_num]
			[TEX_HEIGHT * tex_y + main->tex_x];
		if (main->side == 1)
			main->color = (main->color >> 1) & 8355711;
		draw_pixel(main, x, y, main->color);
		y++;
	}
}

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