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
		setting_up(main, x);
		calcWallDistance(main);
		processingDDA(main);
		if (main->side == 0)
			main->perp_wall_dist = (main->map_x - R_POS_X
				+ (1 - main->step_x) / 2) / R_DIR_X;
		else
			main->perp_wall_dist = (main->map_y - R_POS_Y
				+ (1 - main->step_y) / 2) / R_DIR_Y;
		drawingMath(main, x);
		main_drawcall(x, main);
		x++;
	}
}

void	go_straight(t_main *main)
{
	mlx_destroy_image(main->mlx, main->img);
	img_init(main);
	if (main->maze[(int)(POS_X + main->dir_x
			* main->move_speed)][(int)POS_Y] == 0
			|| ((int)(POS_X + main->dir_x
			* main->move_speed) == 17 && (int)POS_Y == 3))
		POS_X += main->dir_x * main->move_speed;
	if (main->maze[(int)POS_X][(int)(POS_Y
			+ main->dir_y * main->move_speed)] == 0)
		POS_Y += main->dir_y * main->move_speed;
	raycasting(main);
	mlx_put_image_to_window(main->mlx, main->win, main->img, 0, 0);
	Mix_PlayChannelTimed(-1, main->footsteps, 2, 500);
	show_tooltip(main);
}