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

int					main(const int argc, const char *argv[])
{
	t_main	main;

	SDL_Init(SDL_INIT_AUDIO);
	handling_cmd(&main, argc, argv);
	main.mlx = mlx_init();
	main.win = mlx_new_window(main.mlx, WIDTH, HEIGHT, "Wolf3d");
	main.maze = retrieve_maze(main.inf);
	setting_up_main_structure(&main);
	raycasting(&main);
	audio_setup();
	play_main_theme(&main);
	mlx_put_image_to_window(main.mlx, main.win, main.img, 0, 0);
	mlx_hook(main.win, 2, 5, key_binds, &main);
	mlx_hook(main.win, 17, 0, terminate_programe, &main);
	mlx_loop(main.mlx);
	while (1);
	return (0);
}
