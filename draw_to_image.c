#include "wolf.h"

void	vert_line(int x, t_main *env)
{
	int y;
	int d;
	int tex_y;

	y = env->draw_start;
	while (y < env->draw_end)
	{
		d = y * 256 - HEIGHT * 128 + env->line_height * 128;
		tex_y = ((d * TEX_HEIGHT) / env->line_height) / 256;
		env->color = env->textures[env->tex_num]
			[TEX_HEIGHT * tex_y + env->tex_x];
		if (env->side == 1)
			env->color = (env->color >> 1) & 8355711;
		put_px(env, x, y, env->color);
		y++;
	}
}

void	img_init(t_main *env)
{
	env->img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	env->bpp = 32;
	env->e = 0;
	env->data = mlx_get_data_addr(env->img, &env->bpp,
		&env->sline, &env->e);
}

void	put_px(t_main *env, int x, int y, int color)
{
	int r;
	int g;
	int b;

	r = color % 256;
	g = (color / 256) % 256;
	b = (color / 65536) % 256;
	env->data[((y * env->sline) + (x * 4))] = r;
	env->data[((y * env->sline) + (x * 4)) + 1] = g;
	env->data[((y * env->sline) + (x * 4)) + 2] = b;
}

void	get_textures1(t_main *env)
{
	void	*temp;
	int		b;

	env->textures = (int **)malloc(sizeof(int *) * 11);
	temp = mlx_xpm_file_to_image(env->mlx, "pics/wall-2.xpm",
		&(env->tex_h[0]), &(env->tex_w[0]));
	env->textures[0] = (int *)mlx_get_data_addr(temp, &b, &b, &b);
	temp = mlx_xpm_file_to_image(env->mlx, "pics/ceil_1.xpm",
		&(env->tex_h[1]), &(env->tex_w[1]));
	env->textures[1] = (int *)mlx_get_data_addr(temp, &b, &b, &b);
	temp = mlx_xpm_file_to_image(env->mlx, "pics/wallh.xpm",
		&(env->tex_h[2]), &(env->tex_w[2]));
	env->textures[2] = (int *)mlx_get_data_addr(temp, &b, &b, &b);
	temp = mlx_xpm_file_to_image(env->mlx, "pics/door.xpm",
		&(env->tex_h[3]), &(env->tex_w[3]));
	env->textures[3] = (int *)mlx_get_data_addr(temp, &b, &b, &b);
}

void	get_textures2(t_main *env)
{
	void	*temp;
	int		b;

	temp = mlx_xpm_file_to_image(env->mlx, "pics/floor.xpm",
		&(env->tex_h[4]), &(env->tex_w[4]));
	env->textures[4] = (int *)mlx_get_data_addr(temp, &b, &b, &b);
	temp = mlx_xpm_file_to_image(env->mlx, "pics/4.xpm",
		&(env->tex_h[5]), &(env->tex_w[5]));
	env->textures[5] = (int *)mlx_get_data_addr(temp, &b, &b, &b);
	temp = mlx_xpm_file_to_image(env->mlx, "pics/4.xpm",
		&(env->tex_h[6]), &(env->tex_w[6]));
	env->textures[6] = (int *)mlx_get_data_addr(temp, &b, &b, &b);
	temp = mlx_xpm_file_to_image(env->mlx, "pics/4.xpm",
		&(env->tex_h[7]), &(env->tex_w[7]));
	env->textures[7] = (int *)mlx_get_data_addr(temp, &b, &b, &b);
	temp = mlx_xpm_file_to_image(env->mlx, "pics/door.xpm",
		&(env->tex_h[8]), &(env->tex_w[8]));
	env->textures[8] = (int *)mlx_get_data_addr(temp, &b, &b, &b);
	temp = mlx_xpm_file_to_image(env->mlx, "pics/door.xpm",
		&(env->tex_h[9]), &(env->tex_w[9]));
	env->textures[9] = (int *)mlx_get_data_addr(temp, &b, &b, &b);
	temp = mlx_xpm_file_to_image(env->mlx, "pics/door.xpm",
		&(env->tex_h[10]), &(env->tex_w[10]));
	env->textures[10] = (int *)mlx_get_data_addr(temp, &b, &b, &b);
}
