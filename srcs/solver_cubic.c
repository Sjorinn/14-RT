/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_cubic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <gbianco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 00:06:45 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/04 20:37:11 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "solver.h"

int			iszero(double x)
{
	return (x > -SOLVER_EPSILON && x < SOLVER_EPSILON);
}

static void	cubic_conditions(double *t, t_cubic *cb)
{
	if (iszero(cb->d))
	{
		if (iszero(cb->q))
		{
			t[0] = 0;
			cb->num = 1;
		}
		else
		{
			cb->u = ft_cube_root(-cb->q);
			t[0] = 2. * cb->u;
			t[1] = -cb->u;
			cb->num = 2;
		}
	}
	else
	{
		cb->phi = 1. / 3. * acos(-cb->q / sqrt(-cb->cb_p));
		cb->t = 2. * sqrt(-cb->p);
		t[0] = cb->t * cos(cb->phi);
		t[1] = -cb->t * cos(cb->phi + M_PI / 3.);
		t[2] = -cb->t * cos(cb->phi - M_PI / 3.);
		cb->num = 3;
	}
}

int			cubic_solver(double *c, double *t)
{
	t_cubic	cb;

	cb.a = c[2] / c[3];
	cb.b = c[1] / c[3];
	cb.c = c[0] / c[3];
	cb.sq_a = cb.a * cb.a;
	cb.p = 1. / 3. * (-1. / 3. * cb.sq_a + cb.b);
	cb.q = 1. / 2. * (2. / 27. * cb.a * cb.sq_a - 1. / 3. * cb.a * cb.b + cb.c);
	cb.cb_p = cb.p * cb.p * cb.p;
	cb.d = cb.q * cb.q + cb.cb_p;
	if (iszero(cb.d) != 0 || cb.d < 0)
		cubic_conditions(t, &cb);
	else
	{
		cb.r_sqrt = sqrt(cb.d);
		cb.r_u = ft_cube_root(cb.r_sqrt - cb.q);
		cb.r_v = -ft_cube_root(cb.r_sqrt + cb.q);
		t[0] = cb.r_u + cb.r_v;
		cb.num = 1;
	}
	cb.sub = 1. / 3. * cb.a;
	cb.i = -1;
	while (++cb.i < cb.num)
		t[cb.i] -= cb.sub;
	return (cb.num);
}
