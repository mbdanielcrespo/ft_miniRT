/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:55:29 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/02 13:18:54 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

int	intersect_plane(t_xyz pos, t_xyz pix_dir, t_plane *pl, t_xyz *ip)
{
	double	dot_nd;
	double	t;
	t_xyz	vec_op;

	dot_nd = dot(pl->norm_vect, pix_dir);
	if (fabs(dot_nd) < 1e-6)
		return (0);
	vec_op = subtr_v(pl->position, pos);
	t = dot(vec_op, pl->norm_vect) / dot_nd;
	if (t < 0)
		return (0);
	*ip = add_v(pos, mult_v(pix_dir, t));
	return (1);
}

t_plane	*intersect_planes(t_data *dt, t_xyz pix_dir, t_xyz *ip)
{
	t_plane		*tmp;
	t_plane		*ret;
	double		min_dist;

	ret = NULL;
	min_dist = INFINITY;
	tmp = dt->plane;
	while (tmp)
	{
		if (intersect_plane(dt->camera->position, pix_dir, tmp, ip))
		{
			if (distance(dt->camera->position, *ip) < min_dist)
			{
				min_dist = distance(dt->camera->position, *ip);
				ret = tmp;
			}
		}
		tmp = tmp->next;
	}
	if (ret)
		intersect_plane(dt->camera->position, pix_dir, ret, ip);
	return (ret);
}

int	intersect_planes2(t_data *dt, t_xyz pix_dir, t_xyz *ip)
{
	t_plane		*tmp;

	tmp = dt->plane;
	while (tmp)
	{
		if (intersect_plane(dt->light->position, pix_dir, tmp, ip))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
