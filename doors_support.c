/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_support.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 13:41:48 by rbozhko           #+#    #+#             */
/*   Updated: 2019/04/28 13:41:50 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		**retrieve_maze(char *str)
{
	int		**maze;
	char	**tmp;
	int		k;
	int		i;
	int		j;

	i = 0;
	maze = (int **)malloc(sizeof(int *) * MAP_HEIGHT);
	tmp = ft_strsplit(str, '\n');
	while (tmp[i])
	{
		j = 0;
		k = 0;
		maze[i] = (int *)malloc(sizeof(int) * MAP_WIDTH);
		while (tmp[i][j] != '\0')
		{
			if (tmp[i][j] >= '0' && tmp[i][j] <= '9')
				maze[i][k++] = tmp[i][j] - '0';
			j++;
		}
		i++;
	}
	ft_free_bidarr(tmp, i);
	return (maze);
}

char	*read_from_file(int fd)
{
	char	*inf;
	char	*temp;
	char	*buffer;
	int		r;

	buffer = (char *)malloc(sizeof(char) * 9001);
	inf = (char *)malloc(sizeof(char));
	if ((r = read(fd, buffer, 0)) < 0)
	{
		ft_throw_exception("Passed argument couldn't be read");
	}
	while ((r = read(fd, buffer, 9000)) > 0)
	{
		buffer[r] = '\0';
		temp = inf;
		inf = ft_strjoin(inf, buffer);
		ft_strdel(&temp);
	}
	ft_strdel(&buffer);
	if (!ft_strlen(inf))
	{
		free(inf);
		inf = NULL;
	}
	return (inf);
}

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

void	open_door(t_main *main)
{
	if (main->maze[15][11] == 4)
		main->maze[15][11] = 0;
	else
		main->maze[15][11] = 4;
	mlx_destroy_image(main->mlx, main->img);
	img_init(main);
	Mix_PlayChannel(-1, main->door_open, 0);
	main->door = 0;
	raycasting(main);
	mlx_put_image_to_window(main->mlx, main->win, main->img, 0, 0);
}
