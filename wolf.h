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


# define INTERACT "PRESS <SPACE> TO INTERACT"

# define BPP 32

# define WIDTH 1920

# define POS_X main->pos_x
# define HEIGHT 1080

# define MLX main->mlx
# define WIN main->win

# define R_POS_Y main->ray_pos_y
# define PLN_Y main->plane_y

# define NUM_SPRITES 3
# define R_POS_X main->ray_pos_x
# define PLN_X main->plane_x

# define MAP_WIDTH 24
# define R_DIR_X main->ray_dir_x
# define MAP_HEIGHT 24
# define R_DIR_Y main->ray_dir_y
# define TEX_WIDTH 129
# define POS_Y main->pos_y
# define TEX_HEIGHT 129


typedef struct	s_main
{
	int			**maze;
	int			**textures;
	char		*inf;
	double		dir_y;
	double		pos_x;
	int			tex_w[11];
	double		pos_y;
	double		dir_x;
	double		ray_pos_x;
	double		plane_x;
	double		camera_x;
	double		plane_y;
	double		ray_pos_y;
	int			for_side;
	void		*mlx;
	double		ray_dir_x;
	int			door;
	void		*win;
	void		*img;
	int			map_x;
	int			bpp;
	int			draw_end;
	int			color;
	int			draw_start;
	int			sline;
	double		ray_dir_y;
	int			e;
	char		*data;
	double		side_dist_x;
	double		cur_flr_y;
	double		side_dist_y;
	int			floor_tex_x;
	double		floor_x_wall;
	double		dist_player;
	double		floor_y_wall;
	double		dist_wall;
	double		current_dist;
	double		cur_flr_x;
	double		weight;
	double		delta_dist_x;
	int			map_y;
	double		perp_wall_dist;
	double		delta_dist_y;
	int			floor_tex_y;
	int			step_x;
	int			line_height;
	int			step_y;
	int			side;
	int			tex_num;
	int			tex_x;
	int			tex_h[11];
	
	Mix_Chunk	*footsteps;
	Mix_Chunk	*door_open;
	Mix_Music	*main_theme;

	double		move_speed;
}				t_main;

void			ft_init_st(struct jpeg_compress_struct *c, FILE *o);
unsigned char	*ft_get_proper(t_main *main);
int				key_binds(int keycode, t_main *main);
void			play_main_theme(t_main *main);
void			clean_up(t_main *main);
int				terminate_programe(void);
void			calculate_drawing_data(t_main *main, int y);
void			setting_up_main_structure(t_main *main);
void			img_init(t_main *main);
void			upload_textures(t_main *main);
void			handling_cmd(t_main *main, const int argc, const char *argv[]);
void			draw_line(int x, t_main *main);
void			draw_floor(t_main *main, double wall_x);
void			main_drawcall(int x, t_main *main);
void			raycasting(t_main *main);
void			setting_up(t_main *main, int x);
char			*read_from_file(int fd);
int				**retrieve_maze(char *str);
void			calcWallDistance(t_main *main);
FILE			*ft_get_file(void);
void			processingDDA(t_main *main);
void			go_straight(t_main *main);
void			go_back(t_main *main);
void			drawingMath(t_main *main, int x);
void			show_tooltip(t_main *main);
void			go_leftside(t_main *main);
void			go_rightside(t_main *main);
int				mouse_control(int x, t_main *main);
void			open_door(t_main *main);
int				ft_make_printscreen(t_main *main);
void			four_sided(t_main *main);
void			audio_setup();
void			draw_pixel(t_main *main, int x, int y, int color);

#endif
