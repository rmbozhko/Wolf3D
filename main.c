/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 13:42:10 by rbozhko           #+#    #+#             */
/*   Updated: 2019/04/28 14:00:32 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdio.h>
static int			key_binds(int keycode, t_main *main)
{
	if (keycode == 53)
	{
		clean_up(main);
		exit(1);
	}
	if (keycode == 13)
		move_forward(main);
	if (keycode == 1)
		move_backward(main);
	if (keycode == 0)
		rotate_left(main);
	if (keycode == 2)
		rotate_right(main);
	if (keycode == 49 && main->door == 1)
		unlock_door(main);
	if (keycode == 35)
		ft_make_printscreen(main);
	return (0);
}

static int			exit_pr(void)
{
	exit(1);
	return (0);
}

static void			starting_setup(t_main *main)
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
}

static void			pars(t_main *main, int ac, char **av)
{
	int		fd;
	char	*inf;

	if (ac != 2)
		ft_throw_exception("No map was passed into project");
	fd = open(av[1], O_RDONLY);
	if (ft_strcmp(av[1], "maps/1.wolf") == 0)
		main->for_side = 1;
	else
		main->for_side = 0;
	inf = read_from_file(fd);
	if (inf)
		main->inf = inf;
	else
		ft_throw_exception("No map data was read");
}

int					main(int ac, char **av)
{
	t_main	main;

	SDL_Init(SDL_INIT_AUDIO);
	pars(&main, ac, av);
	main.mlx = mlx_init();
	main.win = mlx_new_window(main.mlx, WIDTH, HEIGHT, "Wolf3d");
	img_init(&main);
	main.world_map = get_world_map(main.inf);
	starting_setup(&main);
	get_textures1(&main);
	get_textures2(&main);
	raycasting(&main);
	audio_setup();
	play_main_theme(&main);
	mlx_put_image_to_window(main.mlx, main.win, main.img, 0, 0);
	mlx_hook(main.win, 2, 5, key_binds, &main);
	mlx_hook(main.win, 17, 0, exit_pr, &main);
	mlx_loop(main.mlx);
	while (1);
	return (0);
}
