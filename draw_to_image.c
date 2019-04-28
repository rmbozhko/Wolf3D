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

void	vert_line(int x, t_main *main)
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
		put_px(main, x, y, main->color);
		y++;
	}
}

void	img_init(t_main *main)
{
	main->img = mlx_new_image(main->mlx, WIDTH, HEIGHT);
	main->bpp = 32;
	main->e = 0;
	main->data = mlx_get_data_addr(main->img, &main->bpp,
		&main->sline, &main->e);
}

void	put_px(t_main *main, int x, int y, int color)
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

void	get_textures1(t_main *main)
{
	void	*temp;
	int		b;

	main->textures = (int **)malloc(sizeof(int *) * 11);
	temp = mlx_xpm_file_to_image(main->mlx, "pics/wall-2.xpm",
		&(main->tex_h[0]), &(main->tex_w[0]));
	main->textures[0] = (int *)mlx_get_data_addr(temp, &b, &b, &b);
	temp = mlx_xpm_file_to_image(main->mlx, "pics/ceil_1.xpm",
		&(main->tex_h[1]), &(main->tex_w[1]));
	main->textures[1] = (int *)mlx_get_data_addr(temp, &b, &b, &b);
	temp = mlx_xpm_file_to_image(main->mlx, "pics/wallh.xpm",
		&(main->tex_h[2]), &(main->tex_w[2]));
	main->textures[2] = (int *)mlx_get_data_addr(temp, &b, &b, &b);
	temp = mlx_xpm_file_to_image(main->mlx, "pics/door.xpm",
		&(main->tex_h[3]), &(main->tex_w[3]));
	main->textures[3] = (int *)mlx_get_data_addr(temp, &b, &b, &b);
}

void	get_textures2(t_main *main)
{
	void	*temp;
	int		b;

	temp = mlx_xpm_file_to_image(main->mlx, "pics/floor.xpm",
		&(main->tex_h[4]), &(main->tex_w[4]));
	main->textures[4] = (int *)mlx_get_data_addr(temp, &b, &b, &b);
	temp = mlx_xpm_file_to_image(main->mlx, "pics/4.xpm",
		&(main->tex_h[5]), &(main->tex_w[5]));
	main->textures[5] = (int *)mlx_get_data_addr(temp, &b, &b, &b);
	temp = mlx_xpm_file_to_image(main->mlx, "pics/4.xpm",
		&(main->tex_h[6]), &(main->tex_w[6]));
	main->textures[6] = (int *)mlx_get_data_addr(temp, &b, &b, &b);
	temp = mlx_xpm_file_to_image(main->mlx, "pics/4.xpm",
		&(main->tex_h[7]), &(main->tex_w[7]));
	main->textures[7] = (int *)mlx_get_data_addr(temp, &b, &b, &b);
	temp = mlx_xpm_file_to_image(main->mlx, "pics/door.xpm",
		&(main->tex_h[8]), &(main->tex_w[8]));
	main->textures[8] = (int *)mlx_get_data_addr(temp, &b, &b, &b);
	temp = mlx_xpm_file_to_image(main->mlx, "pics/door.xpm",
		&(main->tex_h[9]), &(main->tex_w[9]));
	main->textures[9] = (int *)mlx_get_data_addr(temp, &b, &b, &b);
	temp = mlx_xpm_file_to_image(main->mlx, "pics/door.xpm",
		&(main->tex_h[10]), &(main->tex_w[10]));
	main->textures[10] = (int *)mlx_get_data_addr(temp, &b, &b, &b);
}
