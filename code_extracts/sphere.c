/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apula <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 04:40:30 by apula             #+#    #+#             */
/*   Updated: 2019/06/27 23:59:38 by apula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3			normal_sphere(t_data *dat)
{
	return (v3_ver(dat->obj->pos, dat->intsc));
}

static double	equation(double a, double b, double disc)
{
	double t;
	double t2;

	t = (sqrt(disc) - b) / (2.0 * a);
	t2 = (-sqrt(disc) - b) / (2.0 * a);
	if (t <= 0)
		t = -1;
	if (t2 <= 0)
		t2 = -1;
	return (t <= t2 ? t : t2);
}

double			intersect_ray_sphere(t_ray *r, t_obj *o)
{
	t_vec3	coef;
	double	disc;
	t_vec3	dist;
	double	t;

	coef.x = v3_dot(r->dir, r->dir);
	dist = v3_dif(r->ori, o->pos);
	coef.y = 2 * v3_dot(r->dir, dist);
	coef.z = v3_dot(dist, dist) - (o->dim * o->dim);
	disc = coef.y * coef.y - 4 * coef.x * coef.z;
	if (disc < 0)
		return (0);
	else
	{
		t = equation(coef.x, coef.y, disc);
		return (t);
	}
}
