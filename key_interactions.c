#include "wolf.h"

void	move_forward(t_main *main)
{
	mlx_destroy_image(main->mlx, main->img);
	img_init(main);
	if (main->world_map[(int)(POS_X + main->dir_x
			* main->move_speed)][(int)POS_Y] == 0
			|| ((int)(POS_X + main->dir_x
			* main->move_speed) == 17 && (int)POS_Y == 3))
		POS_X += main->dir_x * main->move_speed;
	if (main->world_map[(int)POS_X][(int)(POS_Y
			+ main->dir_y * main->move_speed)] == 0)
		POS_Y += main->dir_y * main->move_speed;
	raycasting(main);
	mlx_put_image_to_window(main->mlx, main->win, main->img, 0, 0);
	Mix_PlayChannelTimed(-1, main->footsteps, 2, 500);
	show_tooltip(main);
}

void	move_backward(t_main *main)
{
	mlx_destroy_image(main->mlx, main->img);
	img_init(main);
	if (main->world_map[(int)(POS_X - main->dir_x
			* main->move_speed)][(int)POS_Y] == 0
			|| ((int)(POS_X - main->dir_x
			* main->move_speed) == 17 && (int)POS_Y == 3))
		POS_X -= main->dir_x * main->move_speed;
	if (main->world_map[(int)POS_X][(int)(POS_Y
			- main->dir_y * main->move_speed)] == 0)
		POS_Y -= main->dir_y * main->move_speed;
	raycasting(main);
	mlx_put_image_to_window(main->mlx, main->win, main->img, 0, 0);
	Mix_PlayChannelTimed(-1, main->footsteps, 2, 500);
	show_tooltip(main);
}

void	rotate_left(t_main *main)
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

void	rotate_right(t_main *main)
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
