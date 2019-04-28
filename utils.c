#include "wolf.h"

void	img_init(t_main *main)
{
	main->img = mlx_new_image(main->mlx, WIDTH, HEIGHT);
	main->bpp = BPP;
	main->e = 0;
	main->data = mlx_get_data_addr(main->img, &main->bpp,
		&main->sline, &main->e);
}

int			key_binds(int keycode, t_main *main)
{
	if (keycode == 53)
	{
		clean_up(main);
		exit(1);
	}
	if (keycode == 13)
		go_straight(main);
	if (keycode == 1)
		go_back(main);
	if (keycode == 0)
		go_leftside(main);
	if (keycode == 2)
		go_rightside(main);
	if (keycode == 49 && main->door == 1)
		unlock_door(main);
	if (keycode == 35)
		ft_make_printscreen(main);
	return (0);
}

int			terminate_programe(void)
{
	exit(0);
	return (0);
}

void			setting_up_main_structure(t_main *main)
{
	int i;

	POS_X = 22;
	POS_Y = 11.5;
	main->dir_x = -1;
	main->dir_y = 0;
	PLN_X = 0;
	PLN_Y = 0.66;
	main->move_speed = 0.2;
	i = 0;
	img_init(main);
	while (i < 11)
	{
		main->tex_h[i] = TEX_HEIGHT;
		i++;
	}
	i = 0;
	while (i < 11)
	{
		main->tex_w[i] = TEX_WIDTH;
		i++;
	}
	upload_textures(main);
}

void			handling_cmd(t_main *main, const int argc, const char *argv[])
{
	int		fd;
	char	*inf;

	if (argc != 2)
		ft_throw_exception("No map was passed into project");
	fd = open(argv[1], O_RDONLY);
	if (ft_strcmp(argv[1], "maps/1.wolf") == 0)
		main->for_side = 1;
	else
		main->for_side = 0;
	inf = read_from_file(fd);
	if (inf)
		main->inf = inf;
	else
		ft_throw_exception("No map data was read");
}

