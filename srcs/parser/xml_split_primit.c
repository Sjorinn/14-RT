/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_split_primit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 17:10:07 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/05 20:04:27 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		continue_init(char **elm, char *obj)
{
	elm[12] = ft_strinstr(obj, "<texture_file>", "</texture_file>");
	elm[13] = ft_strinstr(obj, "<texture_mode>", "</texture_mode>");
	elm[14] = ft_strinstr(obj, "<bump_map>", "</bump_map>");
	elm[15] = ft_strinstr(obj, "<nrm_sin_pow>", "</nrm_sin_pow>");
	elm[16] = ft_strinstr(obj, "<nrm_sin_frq>", "</nrm_sin_frq>");
	elm[17] = ft_strinstr(obj, "<negatif>", "</negatif>");
	elm[18] = ft_strinstr(obj, "<perturbation>", "</perturbation>");
}

static char		**init_prm_array(t_scene *s, char *obj, int i)
{
	char	**elm;

	elm = (char**)ft_secmemalloc(sizeof(char*) * 19);
	elm[0] = ft_strinstr(obj, "<position>", "</position>");
	elm[1] = ft_strinstr(obj, "<direction>", "</direction>");
	elm[2] = ft_strinstr(obj, "<dimension>", "</dimension>");
	elm[3] = ft_strinstr(obj, "<type>", "</type>");
	elm[4] = ft_strinstr(obj, "<color>", "</color>");
	elm[5] = ft_strinstr(obj, "<shine>", "</shine>");
	elm[6] = ft_strinstr(obj, "<motion>", "</motion>");
	elm[7] = ft_strinstr(obj, "<translation>", "</translation>");
	elm[8] = ft_strinstr(obj, "<rotation>", "</rotation>");
	elm[9] = ft_strinstr(obj, "<reflection>", "</reflection>");
	elm[10] = ft_strinstr(obj, "<refraction>", "</refraction>");
	elm[11] = ft_strinstr(obj, "<transparence>", "</transparence>");
	continue_init(elm, obj);
	if (!elm[0] || !elm[1] || !elm[2] || !elm[3] || !elm[4])
		error("Some mandatory object tag is missing");
	s->obj[i].pr = (t_prm*)ft_secmemalloc(sizeof(t_prm));
	return (elm);
}

static void		split_kellum_tags(t_scene *s, char **elm, int i)
{
	t_vec3	text_mode;

	s->obj[i].bump[0] = assign_vector(elm[15]);
	s->obj[i].bump[1] = assign_vector(elm[16]);
	if ((elm[12] || elm[14]))
	{
		if (s->obj[i].typ > 4)
			error("Texture are not compatible with some object type");
		s->obj[i].txt = (t_txt*)ft_secmemalloc(sizeof(t_txt));
		if (elm[12] && (!elm[13]))
			error("Texture mode is missing");
		s->obj[i].txt->filename = assign_char(elm[12]);
		text_mode = assign_vector(elm[13]);
		s->obj[i].txt->stretch = text_mode.x;
		s->obj[i].txt->x_offset = text_mode.y;
		s->obj[i].txt->y_offset = text_mode.z;
		s->obj[i].txt->bumpname = assign_char_double(elm[14],
			&s->obj[i].txt->bump_pow);
	}
}

static void		split_again(t_scene *s, char **elm, int i)
{
	double	pert[2];

	pert[0] = 0;
	pert[1] = 0;
	s->obj[i].neg = elm[17] ? assign_double(elm[17]) : 0;
	assign_bidouble(elm[18], &pert[0], &pert[1]);
	s->obj[i].pert = pert[0];
	s->obj[i].p_clr = pert[1];
}

void			split_primitive_tags(t_scene *s, char *obj, int i)
{
	char	**elm;

	elm = init_prm_array(s, obj, i);
	s->obj[i].id = i - s->n_prt + 1;
	s->obj[i].pr->pos = assign_vector(elm[0]);
	s->obj[i].dir = assign_vector(elm[1]);
	s->obj[i].typ = assign_chartype(elm[3]);
	s->obj[i].pr->dim = assign_double(elm[2]);
	if (s->obj[i].typ == 3)
	{
		ft_degtorad(&s->obj[i].pr->dim);
		s->obj[i].pr->dim = tan(s->obj[i].pr->dim / 2.);
	}
	s->obj[i].clr = assign_hex(elm[4]);
	assign_bidouble(elm[5], &s->obj[i].shi[0], &s->obj[i].shi[1]);
	s->obj[i].blur = assign_vector(elm[6]);
	s->obj[i].tra = assign_vector(elm[7]);
	s->obj[i].rot = assign_vector(elm[8]);
	s->obj[i].rfl = assign_double(elm[9]);
	s->obj[i].ior = assign_double(elm[10]);
	s->obj[i].tcy = assign_double(elm[11]);
	split_again(s, elm, i);
	if (elm[12] || elm[13] || elm[14] || elm[15] || elm[16])
		split_kellum_tags(s, elm, i);
	ft_strarraydeln(elm, 19, 1);
}
