/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:34:45 by rbozhko           #+#    #+#             */
/*   Updated: 2019/04/28 13:45:51 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "libft/libft.h"
# include <stdio.h>
# include <math.h>
# include <SDL.h>
# include "SDL_mixer.h"
# include <mlx.h>
# include <OpenCL/opencl.h>
# include "jpeglib/jpeglib.h"

# define MLX main->mlx
# define WIN main->win
# define POS_X main->pos_x
# define POS_Y main->pos_y
# define R_POS_X main->ray_pos_x
# define R_POS_Y main->ray_pos_y
# define PLN_Y main->plane_y
# define PLN_X main->plane_x
# define R_DIR_X main->ray_dir_x
# define R_DIR_Y main->ray_dir_y

# define INTERACT "PRESS <SPACE> TO INTERACT"

# define WIDTH 1920
# define HEIGHT 1080

# define MAP_WIDTH 24
# define MAP_HEIGHT 24

# define TEX_WIDTH 129
# define TEX_HEIGHT 129

# define NUM_SPRITES 3

typedef struct	s_main
{
	int			door;
	int			for_side;
	void		*mlx;
	void		*win;

	void		*img;
	int			bpp;
	int			sline;
	int			e;
	char		*data;

	int			**maze;
	int			**textures;
	int			tex_h[11];
	int			tex_w[11];

	char		*inf;

	double		pos_x;
	double		pos_y;

	double		dir_x;
	double		dir_y;

	double		plane_x;
	double		plane_y;

	double		camera_x;
	double		ray_pos_x;
	double		ray_pos_y;
	double		ray_dir_x;
	double		ray_dir_y;

	int			map_x;
	int			map_y;

	double		side_dist_x;
	double		side_dist_y;

	double		floor_x_wall;
	double		floor_y_wall;
	double		dist_wall;
	double		dist_player;
	double		current_dist;
	double		cur_flr_x;
	double		cur_flr_y;
	int			floor_tex_x;
	int			floor_tex_y;
	double		weight;

	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;

	int			step_x;
	int			step_y;

	int			side;

	int			line_height;
	int			draw_start;
	int			draw_end;
	int			color;

	int			tex_x;
	int			tex_num;

	Mix_Chunk	*footsteps;
	Mix_Chunk	*door_open;
	Mix_Music	*main_theme;

	double		move_speed;
}				t_main;


int				key_binds(int keycode, t_main *main);
int				terminate_programe(void);
void			setting_up_main_structure(t_main *main);
void			handling_cmd(t_main *main, const int argc, const char *argv[]);

void			vert_line(int x, t_main *main);
void			img_init(t_main *main);
void			put_px(t_main *main, int x, int y, int color);
void			upload_textures(t_main *main);

char			*read_from_file(int fd);
int				**retrieve_maze(char *str);

void			raycasting(t_main *main);
void			init(t_main *main, int x);
void			calc_sidedist_n_step(t_main *main);
void			perform_dda(t_main *main);
void			calc_for_draw(t_main *main, int x);
void			draw_ground(t_main *main, double wall_x);
void			main_drawcall(int x, t_main *main);

void			go_straight(t_main *main);
void			go_back(t_main *main);
void			go_leftside(t_main *main);
void			go_rightside(t_main *main);
int				mouse_control(int x, t_main *main);
void			unlock_door(t_main *main);
int				ft_make_printscreen(t_main *main);

void			show_tooltip(t_main *main);
void			four_sided(t_main *main);

void			audio_setup();
void			play_main_theme(t_main *main);
void			clean_up(t_main *main);

#endif
