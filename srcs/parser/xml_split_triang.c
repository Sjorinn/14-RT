/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_split_triang.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 17:10:15 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/04 13:29:18 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static char	**init_trn_array(t_scene *s, char *obj, int i)
{
	char	**trn;

	trn = (char**)ft_secmemalloc(sizeof(char*) * 14);
	trn[0] = ft_strinstr(obj, "<vertex1>", "</vertex1>");
	trn[1] = ft_strinstr(obj, "<vertex2>", "</vertex2>");
	trn[2] = ft_strinstr(obj, "<vertex3>", "</vertex3>");
	trn[3] = ft_strinstr(obj, "<type>", "</type>");
	trn[4] = ft_strinstr(obj, "<color>", "</color>");
	trn[5] = ft_strinstr(obj, "<shine>", "</shine>");
	trn[6] = ft_strinstr(obj, "<motion>", "</motion>");
	trn[7] = ft_strinstr(obj, "<normal>", "</normal>");
	trn[8] = ft_strinstr(obj, "<translation>", "</translation>");
	trn[9] = ft_strinstr(obj, "<rotation>", "</rotation>");
	trn[10] = ft_strinstr(obj, "<reflection>", "</reflection>");
	trn[11] = ft_strinstr(obj, "<refraction>", "</refraction>");
	trn[12] = ft_strinstr(obj, "<trasparence>", "</trasparence>");
	trn[13] = ft_strinstr(obj, "<negatif>", "</negatif>");
	if (!trn[0] || !trn[1] || !trn[2] || !trn[3] || !trn[4])
		error("Some mandatory triangle tag is missing");
	s->obj[i].tr = (t_trn*)ft_secmemalloc(sizeof(t_trn));
	return (trn);
}

void		split_triangle_tags(t_scene *s, char *obj, int i)
{
	char	**trn;

	trn = init_trn_array(s, obj, i);
	s->obj[i].tr->v0 = assign_vector(trn[0]);
	s->obj[i].tr->v1 = assign_vector(trn[1]);
	s->obj[i].tr->v2 = assign_vector(trn[2]);
	s->obj[i].typ = 5;
	s->obj[i].clr = assign_hex(trn[4]);
	s->obj[i].id = i - s->n_prt + 1;
	assign_bidouble(trn[5], &s->obj[i].shi[0], &s->obj[i].shi[1]);
	s->obj[i].blur = assign_vector(trn[6]);
	s->obj[i].dir = assign_vector(trn[7]);
	s->obj[i].tra = assign_vector(trn[8]);
	s->obj[i].rot = assign_vector(trn[9]);
	s->obj[i].rfl = assign_double(trn[10]);
	s->obj[i].ior = assign_double(trn[11]);
	s->obj[i].tcy = assign_double(trn[12]);
	s->obj[i].neg = trn[13] ? assign_double(trn[13]) : 0;
	ft_strarraydeln(trn, 14, 1);
}
