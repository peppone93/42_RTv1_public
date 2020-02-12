/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 00:51:40 by gbianco           #+#    #+#             */
/*   Updated: 2019/06/28 01:04:37 by apula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		get_color(t_scene *s, double en[])
{
	double	tot;
	t_vec3	rgb;
	t_vec3	lcl;
	int		c[2];

	c[1] = s->data.obj->clr;
	rgb = v3((c[1] >> 16), ((c[1] >> 8) & 0xFF), (c[1] & 0xFF));
	rgb = v3_scp(rgb, s->ambient);
	lcl = v3(0, 0, 0);
	tot = 0;
	c[0] = -1;
	while (++c[0] < s->n_lht)
	{
		en[c[0]] = atan(en[c[0]]) * 0.63662;
		lcl.x += (s->lht[c[0]].clr >> 16) * en[c[0]] * 255;
		lcl.y += ((s->lht[c[0]].clr >> 8) & 0xFF) * en[c[0]] * 255;
		lcl.z += (s->lht[c[0]].clr & 0xFF) * en[c[0]] * 255;
		tot += en[c[0]];
	}
	tot = tot / (double)s->n_lht;
	rgb = v3_add(rgb, v3_scp(v3_dif(lcl, rgb), tot));
	rgb.x = rgb.x > 255 ? 255 : rgb.x;
	rgb.y = rgb.y > 255 ? 255 : rgb.y;
	rgb.z = rgb.z > 255 ? 255 : rgb.z;
	return (((int)rgb.x << 16) | ((int)rgb.y << 8) | (int)rgb.z);
}

static double	lambert(t_scene *s, t_light *l)
{
	double	sphericdist;
	double	dot;
	t_vec3	intl;

	intl = v3_dif(l->pos, s->data.intsc);
	sphericdist = v3_dot(intl, intl) * (4 * M_PI);
	intl = v3_nor(intl);
	dot = v3_dot(intl, s->data.normal);
	dot = dot < 0 ? 0 : dot;
	return (1.5 * l->pow * dot / sphericdist);
}

static double	phong(t_scene *s, t_light *l)
{
	double	sphericdist;
	double	dot;
	t_vec3	intl;
	t_vec3	vision;
	t_vec3	specular;

	intl = v3_dif(s->data.intsc, l->pos);
	sphericdist = v3_dot(intl, intl) * (4 * M_PI);
	vision = v3_dif(s->data.intsc, s->data.ray.ori);
	vision = v3_nor(vision);
	specular = v3_scp(s->data.normal, (2 * v3_dot(intl, s->data.normal)));
	specular = v3_dif(specular, intl);
	specular = v3_nor(specular);
	dot = v3_dot(specular, vision);
	dot = dot < 0 ? 0 : dot;
	dot = pow(dot, s->data.obj->sh[0]) * s->data.obj->sh[1];
	return (l->pow * dot / sphericdist);
}

static double	shadow(t_scene *s, t_light *l)
{
	t_ray	lightray;
	double	lightdist;
	double	t;
	int		i;

	lightray.ori = v3_add(s->data.intsc, v3_scp(s->data.normal, BIAS));
	lightray.dir = v3_dif(l->pos, lightray.ori);
	lightdist = v3_len(v3(0, 0, 0), lightray.dir);
	lightray.dir = v3_nor(lightray.dir);
	i = -1;
	while (++i < s->n_obj)
	{
		t = intersections(&s->obj[i], &lightray);
		if (t > 0 && t < lightdist)
			return (1);
	}
	return (0);
}

int				light(t_scene *s)
{
	int		i;
	double	en[s->n_lht];

	i = -1;
	while (++i < s->n_lht)
	{
		en[i] = 0;
		if (shadow(s, &s->lht[i]) == 0)
		{
			en[i] += phong(s, &s->lht[i]);
			en[i] += lambert(s, &s->lht[i]);
		}
	}
	return (get_color(s, en));
}
