/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apula <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 19:32:26 by apula             #+#    #+#             */
/*   Updated: 2019/06/25 19:54:41 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	v3(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec3	v3_add(t_vec3 v1, t_vec3 v2)
{
	return (v3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vec3	v3_dif(t_vec3 v1, t_vec3 v2)
{
	return (v3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_vec3	v3_pro(t_vec3 v1, t_vec3 v2)
{
	return (v3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z));
}

t_vec3	v3_div(t_vec3 v1, t_vec3 v2)
{
	return (v3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z));
}
