/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pscreen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:36:52 by rbozhko           #+#    #+#             */
/*   Updated: 2019/04/28 13:43:36 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	go_back(t_main *main)
{
	mlx_destroy_image(main->mlx, main->img);
	img_init(main);
	if (main->maze[(int)(POS_X - main->dir_x
			* main->move_speed)][(int)POS_Y] == 0
			|| ((int)(POS_X - main->dir_x
			* main->move_speed) == 17 && (int)POS_Y == 3))
		POS_X -= main->dir_x * main->move_speed;
	if (main->maze[(int)POS_X][(int)(POS_Y
			- main->dir_y * main->move_speed)] == 0)
		POS_Y -= main->dir_y * main->move_speed;
	raycasting(main);
	mlx_put_image_to_window(main->mlx, main->win, main->img, 0, 0);
	Mix_PlayChannelTimed(-1, main->footsteps, 2, 500);
	show_tooltip(main);
}

void	calcWallDistance(t_main *main)
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

void	calculate_drawing_data(t_main *main, int y)
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

unsigned char	*ft_get_proper(t_main *main)
{
	unsigned char		*temp;
	size_t				i;
	size_t				j;
	unsigned long		len;

	i = 0;
	j = 0;
	len = HEIGHT * main->sline;
	temp = (unsigned char*)malloc(sizeof(char) * HEIGHT * WIDTH * 3 + 1);
	ft_bzero(temp, sizeof(char) * HEIGHT * WIDTH * 3 + 1);
	while (i < len && j < len)
	{
		if (((j + 1) % 4) == 0)
			j++;
		temp[i++] = main->data[j + 2];
		temp[i++] = main->data[j + 1];
		temp[i++] = main->data[j];
		j += 3;
	}
	return (temp);
}
