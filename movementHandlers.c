/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_interactions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 13:42:05 by rbozhko           #+#    #+#             */
/*   Updated: 2019/04/28 13:42:06 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	setting_up(t_main *main, int x)
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

void				ft_init_st(struct jpeg_compress_struct *c, FILE *o)
{
	struct jpeg_error_mgr		jerr;

	c->err = jpeg_std_error(&jerr);
	jpeg_create_compress(c);
	jpeg_stdio_dest(c, o);
	c->image_width = WIDTH;
	c->image_height = HEIGHT;
	c->input_components = 3;
	c->in_color_space = JCS_RGB;
	jpeg_set_defaults(c);
	jpeg_start_compress(c, TRUE);
}

FILE				*ft_get_file(void)
{
	char		*filename;
	FILE		*outfile;

	filename = ft_strjoin("Wolf3D", ".jpg");
	outfile = fopen(filename, "wb");
	ft_strdel(&filename);
	if (!outfile)
		ft_throw_exception("Error opening output jpeg file.\n");
	return (outfile);
}

void	go_leftside(t_main *main)
{
	double old_dir_x;
	double old_plane_x;

	mlx_destroy_image(main->mlx, main->img);
	img_init(main);
	old_dir_x = main->dir_x;
	main->dir_x = main->dir_x * cos(3 * (M_PI / 180))
				- main->dir_y * sin(3 * (M_PI / 180));
	main->dir_y = old_dir_x * sin(3 * (M_PI / 180))
				+ main->dir_y * cos(3 * (M_PI / 180));
	old_plane_x = PLN_X;
	PLN_X = PLN_X * cos(3 * (M_PI / 180))
				- PLN_Y * sin(3 * (M_PI / 180));
	PLN_Y = old_plane_x * sin(3 * (M_PI / 180))
				+ PLN_Y * cos(3 * (M_PI / 180));
	raycasting(main);
	mlx_put_image_to_window(main->mlx, main->win, main->img, 0, 0);
	Mix_PlayChannelTimed(-1, main->footsteps, 2, 500);
	show_tooltip(main);
}

void	go_rightside(t_main *main)
{
	double old_dir_x;
	double old_plane_x;

	mlx_destroy_image(main->mlx, main->img);
	img_init(main);
	old_dir_x = main->dir_x;
	main->dir_x = main->dir_x * cos(-3 * (M_PI / 180))
				- main->dir_y * sin(-3 * (M_PI / 180));
	main->dir_y = old_dir_x * sin(-3 * (M_PI / 180))
				+ main->dir_y * cos(-3 * (M_PI / 180));
	old_plane_x = PLN_X;
	PLN_X = PLN_X * cos(-3 * (M_PI / 180))
				- PLN_Y * sin(-3 * (M_PI / 180));
	PLN_Y = old_plane_x * sin(-3 * (M_PI / 180))
				+ PLN_Y * cos(-3 * (M_PI / 180));
	raycasting(main);
	mlx_put_image_to_window(main->mlx, main->win, main->img, 0, 0);
	Mix_PlayChannelTimed(-1, main->footsteps, 2, 500);
	show_tooltip(main);
}
