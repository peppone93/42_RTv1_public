/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apula <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 00:21:31 by apula             #+#    #+#             */
/*   Updated: 2019/06/28 00:34:52 by apula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_vec3	get_norm(t_data *dat)
{
	t_vec3	nrm;

	nrm = dat->obj->dir;
	if (dat->obj->type == 1)
		nrm = normal_sphere(dat);
	else if (dat->obj->type == 2)
		nrm = normal_cylinder(dat);
	else if (dat->obj->type == 3)
		nrm = normal_cone(dat);
	return (nrm);
}

double			intersections(t_obj *o, t_ray *r)
{
	double	t;

	t = 0;
	if (o->type == 0)
		t = intersect_ray_plane(r, o);
	else if (o->type == 1)
		t = intersect_ray_sphere(r, o);
	else if (o->type == 2)
		t = intersect_ray_cylinder(r, o);
	else if (o->type == 3)
		t = intersect_ray_cone(r, o);
	return (t);
}

static void		closer(t_obj *o, t_ray *r, t_data *data)
{
	double t;

	t = intersections(o, r);
	if (t > 0 && t < data->dist)
	{
		data->dist = t;
		data->intsc = v3_scp(r->dir, t);
		data->intsc = v3_add(data->intsc, r->ori);
		data->obj = o;
	}
}

static void		*rendering(void *sv)
{
	int		c[2];
	int		i;
	t_ray	r;
	t_scene	*s;

	s = (t_scene*)sv;
	r.ori = s->c_pos;
	c[1] = s->start - 1;
	while (++c[1] <= (s->start + (s->mlx.hei / THREAD)))
	{
		c[0] = -1;
		while (++c[0] <= s->mlx.wid)
		{
			r.dir = camera(s, c[0], c[1]);
			s->data.ray = r;
			s->data.dist = INFINITY;
			i = -1;
			while (++i < s->n_obj)
				closer(&s->obj[i], &r, &s->data);
			if (s->data.dist != INFINITY)
				s->data.normal = get_norm(&s->data);
			color_pixel(s, c[0], c[1], s->data.dist != INFINITY ? light(s) : 0);
		}
	}
	pthread_exit(NULL);
}

void			multithreading(t_scene s[])
{
	pthread_t	thread[THREAD];
	int			i;
	int			add;

	add = s->mlx.hei / THREAD;
	i = -1;
	while (++i < THREAD)
	{
		if (i != 0)
			s[i] = s[0];
		s[i].start = add * i;
	}
	i = -1;
	while (++i < THREAD)
		pthread_create(&thread[i], NULL, rendering, &s[i]);
	i++;
	while (--i > 0)
		pthread_join(thread[i - 1], NULL);
	mlx_put_image_to_window(s->mlx.ptr, s->mlx.win, s->mlx.im, 0, 0);
}
