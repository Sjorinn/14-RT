/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 03:08:03 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/05 22:58:11 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_H
# define SOLVER_H

# define SOLVER_EPSILON     1e-12

typedef struct	s_cubic
{
	int			i;
	int			num;
	double		sub;
	double		a;
	double		b;
	double		c;
	double		sq_a;
	double		p;
	double		q;
	double		cb_p;
	double		d;
	double		u;
	double		phi;
	double		t;
	double		r_sqrt;
	double		r_u;
	double		r_v;
}				t_cubic;

typedef struct	s_quartic
{
	double		coef[4];
	double		a;
	double		b;
	double		c;
	double		d;
	double		z;
	double		u;
	double		v;
	double		sub;
	double		sq_a;
	double		p;
	double		q;
	double		r;
	int			i;
	int			num;
}				t_quartic;

int				iszero(double x);

#endif
