/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pscreen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:36:52 by rbozhko           #+#    #+#             */
/*   Updated: 2019/04/28 13:43:36 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static FILE				*ft_get_file(void)
{
	char		*filename;
	FILE		*outfile;

	filename = ft_strjoin("Wolf3D", ".jpg");
	outfile = fopen(filename, "wb");
	ft_strdel(&filename);
	if (!outfile)
		ft_throw_exception("Error opening output jpeg file.\n");
	return (outfile);
}

static void				ft_init_st(struct jpeg_compress_struct *c, FILE *o)
{
	struct jpeg_error_mgr		jerr;

	c->err = jpeg_std_error(&jerr);
	jpeg_create_compress(c);
	jpeg_stdio_dest(c, o);
	c->image_width = WIDTH;
	c->image_height = HEIGHT;
	c->input_components = 3;
	c->in_color_space = JCS_RGB;
	jpeg_set_defaults(c);
	jpeg_start_compress(c, TRUE);
}

static unsigned char	*ft_get_proper(t_main *main)
{
	unsigned char		*temp;
	size_t				i;
	size_t				j;
	unsigned long		len;

	i = 0;
	j = 0;
	len = HEIGHT * main->sline;
	temp = (unsigned char*)malloc(sizeof(char) * HEIGHT * WIDTH * 3 + 1);
	ft_bzero(temp, sizeof(char) * HEIGHT * WIDTH * 3 + 1);
	while (i < len && j < len)
	{
		if (((j + 1) % 4) == 0)
			j++;
		temp[i++] = main->data[j + 2];
		temp[i++] = main->data[j + 1];
		temp[i++] = main->data[j];
		j += 3;
	}
	return (temp);
}

int						ft_make_printscreen(t_main *main)
{
	FILE							*outfile;
	struct jpeg_compress_struct		cinfo;
	JSAMPROW						row_pointer[1];
	unsigned char					*temp;

	outfile = ft_get_file();
	ft_init_st(&cinfo, outfile);
	temp = ft_get_proper(main);
	while (cinfo.next_scanline < cinfo.image_height)
	{
		row_pointer[0] = &temp[cinfo.next_scanline * cinfo.image_width
			* cinfo.input_components];
		jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}
	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);
	fclose(outfile);
	ft_strdel((char**)&temp);
	return (1);
}
