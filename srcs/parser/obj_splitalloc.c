/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_splitalloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:00:25 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/04 18:00:31 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static char	line_type_checker(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] && line[i + 1])
	{
		if (line[i] == 'v' && line[i + 1] == ' ')
			return ('v');
		if (line[i] == 'v' && line[i + 1] == 'n')
			return ('n');
		else if (line[i] == 'f')
			return ('f');
	}
	return ('0');
}

void		count_elements(t_objw *objw, char *line)
{
	char	line_type;

	line_type = line_type_checker(line);
	if (line_type == 'v')
		objw->n_vertex++;
	else if (line_type == 'n')
		objw->n_normal++;
	else if (line_type == 'f')
		objw->n_triangle += (ft_count_dig_words(line, ' ') - 2);
	free(line);
	line = 0;
}

void		alloc_elements(t_objw *objw)
{
	objw->v_vertex = (t_vec3*)ft_secmemalloc(sizeof(t_vec3) * objw->n_vertex);
	objw->v_normal = (t_vec3*)ft_secmemalloc(sizeof(t_vec3) * objw->n_normal);
	objw->v_texture = (t_vec3*)ft_secmemalloc(sizeof(t_vec3) * objw->n_texture);
	objw->d_trn = (t_dat3*)ft_secmemalloc(sizeof(t_dat3) * objw->n_triangle);
}

void		split_elements(t_objw *objw, char *line)
{
	char	line_type;
	int		faces;

	faces = 0;
	line_type = line_type_checker(line);
	if (line_type == 'v')
		obj_assign_vertex(objw, line);
	else if (line_type == 'n')
		obj_assign_normal(objw, line);
	else if (line_type == 'f')
	{
		if ((faces = ft_count_dig_words(line, ' ')) == 3)
			obj_assign_triangle(objw, line);
		else if (faces > 3)
			obj_assign_faces(objw, line, faces);
		else
			error("Something faces format is not correct");
	}
	free(line);
	line = 0;
}
