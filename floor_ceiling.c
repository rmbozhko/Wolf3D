/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 13:41:58 by rbozhko           #+#    #+#             */
/*   Updated: 2019/04/28 13:41:58 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	calculate_drawing_data(t_main *main, int y)
{
	main->current_dist = HEIGHT / (2.0 * y - HEIGHT);
	main->weight = (main->current_dist - main->dist_player)
	/ (main->dist_wall - main->dist_player);
	main->cur_flr_x = main->weight * main->floor_x_wall
	+ (1.0 - main->weight) * POS_X;
	main->cur_flr_y = main->weight * main->floor_y_wall
	+ (1.0 - main->weight) * POS_Y;
	main->floor_tex_x = (int)(main->cur_flr_x * TEX_WIDTH) % TEX_WIDTH;
	main->floor_tex_y = (int)(main->cur_flr_y * TEX_HEIGHT) % TEX_HEIGHT;
}

void		main_drawcall(int x, t_main *main)
{
	int		y;

	if (main->draw_end < 0)
		main->draw_end = HEIGHT;
	y = main->draw_end + 1;
	while (y < HEIGHT)
	{
		calculate_drawing_data(main, y);
		if (POS_X <= 7)
			main->color = (main->textures[2]
				[TEX_HEIGHT * main->floor_tex_y + main->floor_tex_x]);
		else
			main->color = (main->textures[4]
				[TEX_HEIGHT * main->floor_tex_y + main->floor_tex_x]);
		draw_pixel(main, x, y, main->color);
		if (POS_X <= 7)
			main->color = (main->textures[2]
				[TEX_HEIGHT * main->floor_tex_y + main->floor_tex_x]);
		else
			main->color = (main->textures[1]
				[TEX_HEIGHT * main->floor_tex_y + main->floor_tex_x]);
		draw_pixel(main, x, HEIGHT - y, main->color);
		y++;
	}
}
