/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 10:26:36 by nkellum           #+#    #+#             */
/*   Updated: 2020/02/06 06:20:18 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init_textures(t_scene *s)
{
	int i;

	i = 0;
	while (i < s->n_obj)
	{
		if (s->obj[i].txt != NULL)
		{
			s->obj[i].txt->data = NULL;
			s->obj[i].txt->bump = NULL;
			if (s->obj[i].txt->filename)
				s->obj[i].txt->data = load_texture(s, s->obj[i].txt->filename);
			if (s->obj[i].txt->bumpname)
				s->obj[i].txt->bump = load_texture(s, s->obj[i].txt->bumpname);
		}
		i++;
	}
}

t_texture	*load_texture(t_scene *s, char *filename)
{
	int			width;
	int			height;
	t_texture	*texture;

	if ((texture = malloc(sizeof(t_texture))) == NULL)
		return (0);
	texture->img_texture_ptr = mlx_xpm_file_to_image(s->mlx.ptr,
		filename, &width, &height);
	if (!(texture->img_texture_ptr))
	{
		ft_printf("Error loading texture file %s.\n", filename);
		ft_memdel((void **)&texture);
		return (NULL);
	}
	texture->img_texture_str = mlx_get_data_addr(texture->img_texture_ptr,
		&(s->mlx.b),
	&(s->mlx.s), &(s->mlx.e));
	texture->width = width;
	texture->height = height;
	texture->filename = filename;
	texture->next = NULL;
	return (texture);
}

t_vec3		get_texel(double u, double v, t_texture *texture)
{
	int		index;
	int		x;
	int		y;
	t_vec3	rgb;

	rgb = v3(0, 0, 0);
	x = u * (texture->width - 1);
	y = v * (texture->height - 1);
	if (x < 0)
		x = texture->width - (-x % texture->width);
	if (y < 0)
		y = texture->height - (-y % texture->height);
	if (x > texture->width - 1)
		x = x % texture->width;
	if (y > texture->height - 1)
		y = y % texture->height;
	index = 4 * (y * texture->width) + 4 * x;
	rgb.z = texture->img_texture_str[index] & 0xFF;
	rgb.y = texture->img_texture_str[index + 1] & 0xFF;
	rgb.x = texture->img_texture_str[index + 2] & 0xFF;
	return (rgb);
}
