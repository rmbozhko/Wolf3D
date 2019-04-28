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