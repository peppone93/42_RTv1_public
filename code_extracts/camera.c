/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apula <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 21:03:32 by apula             #+#    #+#             */
/*   Updated: 2019/06/28 02:56:45 by apula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static	void	rotations(t_scene *s)
{
	double a;
	double b;
	double temp;

	s->c_dir = s->c_init;
	a = s->x_angle * 0.017453;
	b = s->y_angle * 0.017453;
	temp = s->c_dir.x;
	s->c_dir.x = s->c_dir.x * cos(a) + s->c_dir.z * sin(a);
	s->c_dir.z = -temp * sin(a) + s->c_dir.z * cos(a);
	temp = s->c_dir.y;
	s->c_dir.y = s->c_dir.y * cos(b) - s->c_dir.z * sin(b);
	s->c_dir.z = temp * sin(b) + s->c_dir.z * cos(b);
	s->c_dir = v3_nor(s->c_dir);
}

t_vec3			camera(t_scene *s, int x, int y)
{
	t_vec3	u;
	t_vec3	v;
	t_vec3	bottomleft;
	t_vec3	inc[2];
	double	half[2];

	rotations(s);
	u = v3_cro(s->c_dir, v3(0, 1, 0));
	if (s->c_dir.x == 0 && s->c_dir.z == 0 && s->c_dir.y)
		u = v3_cro(s->c_dir, v3(0, 0, 1));
	v = v3_nor(v3_cro(u, s->c_dir));
	u = v3_neg(v3_nor(u));
	half[0] = tan((s->c_fov / (180. / M_PI)) / 2.);
	half[1] = half[0] * ((double)s->mlx.hei / (double)s->mlx.wid);
	bottomleft = v3_dif(s->c_dir, v3_scp(v, half[1]));
	bottomleft = v3_dif(bottomleft, v3_scp(u, half[0]));
	inc[0] = v3_scd(v3_scp(v3_scp(u, 2.), half[0]), s->mlx.wid);
	inc[1] = v3_scd(v3_scp(v3_scp(v, 2.), half[1]), s->mlx.hei);
	inc[0] = v3_scp(inc[0], x);
	inc[1] = v3_scp(inc[1], y);
	return (v3_nor(v3_add(v3_add(bottomleft, inc[0]), inc[1])));
}
