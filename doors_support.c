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

void	unlock_door(t_main *main)
{
	if (main->world_map[15][11] == 4)
		main->world_map[15][11] = 0;
	else
		main->world_map[15][11] = 4;
	mlx_destroy_image(main->mlx, main->img);
	img_init(main);
	Mix_PlayChannel(-1, main->door_open, 0);
	main->door = 0;
	raycasting(main);
	mlx_put_image_to_window(main->mlx, main->win, main->img, 0, 0);
}
