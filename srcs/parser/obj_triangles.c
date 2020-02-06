/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_triangles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 14:34:11 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/04 18:01:10 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	assign_left_block(t_dat3 *d_trn, char *line, int *i)
{
	d_trn->v0 = ft_atoi(&line[*i]);
	while (line[*i] && line[*i] != '/')
	{
		if (line[*i] == ' ')
			return ;
		(*i)++;
	}
	if (line[*i] == '/')
		(*i)++;
	while (line[*i] && line[*i] != '/')
	{
		if (line[*i] == ' ')
			return ;
		(*i)++;
	}
	if (line[*i] == '/')
		(*i)++;
	d_trn->n0 = ft_atoi(&line[*i]);
}

static void	assign_center_block(t_dat3 *d_trn, char *line, int *i)
{
	d_trn->v1 = ft_atoi(&line[*i]);
	while (line[*i] && line[*i] != '/')
	{
		if (line[*i] == ' ')
			return ;
		(*i)++;
	}
	if (line[*i] == '/')
		(*i)++;
	while (line[*i] && line[*i] != '/')
	{
		if (line[*i] == ' ')
			return ;
		(*i)++;
	}
	if (line[*i] == '/')
		(*i)++;
	d_trn->n1 = ft_atoi(&line[*i]);
}

static void	assign_right_block(t_dat3 *d_trn, char *line, int *i)
{
	d_trn->v2 = ft_atoi(&line[*i]);
	while (line[*i] && line[*i] != '/')
	{
		if (line[*i] == ' ')
			return ;
		(*i)++;
	}
	if (line[*i] == '/')
		(*i)++;
	while (line[*i] && line[*i] != '/')
	{
		if (line[*i] == ' ')
			return ;
		(*i)++;
	}
	if (line[*i] == '/')
		(*i)++;
	d_trn->n2 = ft_atoi(&line[*i]);
}

void		obj_assign_triangle(t_objw *objw, char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != 'f')
		i++;
	while (line[i] && ft_isnumber(line[i]) == 0)
		i++;
	assign_left_block(&objw->d_trn[objw->i[3]], line, &i);
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && ft_isnumber(line[i]) == 0)
		i++;
	assign_center_block(&objw->d_trn[objw->i[3]], line, &i);
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && ft_isnumber(line[i]) == 0)
		i++;
	assign_right_block(&objw->d_trn[objw->i[3]], line, &i);
	objw->i[3]++;
}
