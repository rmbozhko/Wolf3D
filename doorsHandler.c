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

void	open_door(t_main *main)
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
