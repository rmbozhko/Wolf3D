/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 13:41:42 by rbozhko           #+#    #+#             */
/*   Updated: 2019/04/28 13:42:49 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		load_files(t_main *main)
{
	main->main_theme = Mix_LoadMUS("/audio/main_theme2.wav");
	main->footsteps = Mix_LoadWAV("/audio/footstep.wav");
	main->door_open = Mix_LoadWAV("/audio/door_open.wav");
}

void			audio_setup(t_main *main)
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	load_files(main);
	Mix_VolumeChunk(main->door_open, 128);
	Mix_VolumeChunk(main->footsteps, 22);
	Mix_VolumeMusic(100);
}

void			play_main_theme(t_main *main)
{
	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(main->main_theme, -1);
}

void			clean_up(t_main *main)
{
	Mix_FreeChunk(main->door_open);
	Mix_FreeChunk(main->footsteps);
	Mix_FreeMusic(main->main_theme);
	Mix_CloseAudio();
	SDL_Quit();
}
