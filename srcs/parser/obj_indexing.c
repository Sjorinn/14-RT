/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_indexing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 14:30:36 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/10 14:57:52 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	secure_deplace(char *line, int *pos)
{
	while (line[*pos] && ft_isnumber(line[*pos]) == 1)
		(*pos)++;
	while (line[*pos] && ft_isnumber(line[*pos]) == 0)
		(*pos)++;
	if (line[*pos] == 0)
		error("The file doesn't respect the 'obj' format");
}

void		obj_assign_vertex(t_objw *objw, char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != 'v')
		i++;
	if (line[i] == '\0')
		error("Wrong vertex format in 'obj' file");
	while (line[i] && ft_isnumber(line[i]) == 0)
		i++;
	objw->v_vertex[objw->i[0]].x = ft_atof(&line[i]);
	secure_deplace(line, &i);
	objw->v_vertex[objw->i[0]].y = ft_atof(&line[i]);
	secure_deplace(line, &i);
	objw->v_vertex[objw->i[0]].z = ft_atof(&line[i]);
	objw->i[0]++;
}

void		obj_assign_normal(t_objw *objw, char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != 'v' && line[i + 1] && line[i + 1] != 'n')
		i++;
	if (line[i] == '\0')
		error("Wrong normal format in 'obj' file");
	while (line[i] && ft_isnumber(line[i]) == 0)
		i++;
	objw->v_normal[objw->i[1]].x = ft_atof(&line[i]);
	secure_deplace(line, &i);
	objw->v_normal[objw->i[1]].y = ft_atof(&line[i]);
	secure_deplace(line, &i);
	objw->v_normal[objw->i[1]].z = ft_atof(&line[i]);
	objw->i[1]++;
}
