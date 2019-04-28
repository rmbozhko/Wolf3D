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

int						ft_make_printscreen(t_main *main)
{
	FILE							*outfile;
	struct jpeg_compress_struct		cinfo;
	JSAMPROW						row_pointer[1];
	unsigned char					*temp;

	outfile = ft_get_file();
	ft_init_st(&cinfo, outfile);
	temp = ft_get_proper(main);
	while (cinfo.next_scanline < cinfo.image_height)
	{
		row_pointer[0] = &temp[cinfo.next_scanline * cinfo.image_width
			* cinfo.input_components];
		jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}
	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);
	fclose(outfile);
	ft_strdel((char**)&temp);
	return (1);
}

void	drawingMath(t_main *main, int x)
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
	draw_line(x, main);
	draw_floor(main, wall_x);
}
