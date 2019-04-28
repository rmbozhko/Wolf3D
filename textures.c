#include "wolf.h"

static void		upload_rest_textures(t_main *main)
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

void	processingDDA(t_main *main)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (main->side_dist_x < main->side_dist_y)
		{
			main->side_dist_x += main->delta_dist_x;
			main->map_x += main->step_x;
			main->side = 0;
		}
		else
		{
			main->side_dist_y += main->delta_dist_y;
			main->map_y += main->step_y;
			main->side = 1;
		}
		if (main->maze[main->map_x][main->map_y] > 0)
			hit = 1;
	}
}

void	upload_textures(t_main *main)
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
	upload_rest_textures(main);
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