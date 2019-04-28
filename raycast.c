/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 13:42:19 by rbozhko           #+#    #+#             */
/*   Updated: 2019/04/28 13:42:20 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	raycasting(t_main *main)
{
	int x;

	x = 0;
	while (x < WIDTH)
	{
		init(main, x);
		calc_sidedist_n_step(main);
		perform_dda(main);
		if (main->side == 0)
			main->perp_wall_dist = (main->map_x - R_POS_X
				+ (1 - main->step_x) / 2) / R_DIR_X;
		else
			main->perp_wall_dist = (main->map_y - R_POS_Y
				+ (1 - main->step_y) / 2) / R_DIR_Y;
		calc_for_draw(main, x);
		main_drawcall(x, main);
		x++;
	}
}

void	init(t_main *main, int x)
{
	main->camera_x = 2 * x / (double)WIDTH - 1;
	R_POS_X = POS_X;
	R_POS_Y = POS_Y;
	R_DIR_X = main->dir_x + PLN_X * main->camera_x;
	R_DIR_Y = main->dir_y + PLN_Y * main->camera_x;
	main->map_x = (int)R_POS_X;
	main->map_y = (int)R_POS_Y;
	main->delta_dist_x = sqrt(1 + (R_DIR_Y * R_DIR_Y)
									/ (R_DIR_X * R_DIR_X));
	main->delta_dist_y = sqrt(1 + (R_DIR_X * R_DIR_X)
									/ (R_DIR_Y * R_DIR_Y));
}

void	calc_sidedist_n_step(t_main *main)
{
	if (R_DIR_X < 0)
	{
		main->step_x = -1;
		main->side_dist_x = (R_POS_X - main->map_x)
			* main->delta_dist_x;
	}
	else
	{
		main->step_x = 1;
		main->side_dist_x = (main->map_x + 1.0 - R_POS_X)
			* main->delta_dist_x;
	}
	if (R_DIR_Y < 0)
	{
		main->step_y = -1;
		main->side_dist_y = (R_POS_Y - main->map_y)
			* main->delta_dist_y;
	}
	else
	{
		main->step_y = 1;
		main->side_dist_y = (main->map_y + 1.0 - R_POS_Y)
			* main->delta_dist_y;
	}
}

void	perform_dda(t_main *main)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (main->side_dist_x < main->side_dist_y)
		{
			main->side_dist_x += main->delta_dist_x;
			main->map_x += main->step_x;
			main->side = 0;
		}
		else
		{
			main->side_dist_y += main->delta_dist_y;
			main->map_y += main->step_y;
			main->side = 1;
		}
		if (main->maze[main->map_x][main->map_y] > 0)
			hit = 1;
	}
}

void	calc_for_draw(t_main *main, int x)
{
	double wall_x;

	main->line_height = (int)(HEIGHT / main->perp_wall_dist);
	main->draw_start = -main->line_height / 2 + HEIGHT / 2;
	if (main->draw_start < 0)
		main->draw_start = 0;
	main->draw_end = main->line_height / 2 + HEIGHT / 2;
	if (main->draw_end >= HEIGHT)
		main->draw_end = HEIGHT - 1;
	main->tex_num = main->maze[main->map_x][main->map_y] - 1;
	if (main->side == 0)
		wall_x = R_POS_Y + main->perp_wall_dist * R_DIR_Y;
	else
		wall_x = R_POS_X + main->perp_wall_dist * R_DIR_X;
	wall_x -= floor((wall_x));
	main->tex_x = (int)(wall_x * (double)TEX_WIDTH);
	if (main->side == 0 && R_DIR_X > 0)
		main->tex_x = TEX_WIDTH - main->tex_x - 1;
	if (main->side == 1 && R_DIR_Y < 0)
		main->tex_x = TEX_WIDTH - main->tex_x - 1;
	if (main->for_side == 1)
		four_sided(main);
	vert_line(x, main);
	draw_floor(main, wall_x);
}
