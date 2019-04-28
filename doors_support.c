/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_support.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 13:41:48 by rbozhko           #+#    #+#             */
/*   Updated: 2019/04/28 13:41:50 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	show_tooltip(t_main *main)
{
	if (((int)POS_X >= 16 && (int)POS_X < 17)
		&& (int)POS_Y == 11)
	{
		mlx_string_put(main->mlx, main->win,
			900, 540, 0x6752d9, INTERACT);
		main->door = 1;
	}
	else
		main->door = 0;
}

void	four_sided(t_main *main)
{
	if (main->side == 0 && R_DIR_X > 0)
		main->tex_num = 1;
	else if (main->side == 0 && R_DIR_X < 0)
		main->tex_num = 2;
	else if (main->side == 1 && R_DIR_Y > 0)
		main->tex_num = 3;
	else
		main->tex_num = 4;
}

void	unlock_door(t_main *main)
{
	if (main->maze[15][11] == 4)
		main->maze[15][11] = 0;
	else
		main->maze[15][11] = 4;
	mlx_destroy_image(main->mlx, main->img);
	img_init(main);
	Mix_PlayChannel(-1, main->door_open, 0);
	main->door = 0;
	raycasting(main);
	mlx_put_image_to_window(main->mlx, main->win, main->img, 0, 0);
}
