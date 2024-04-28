/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:55:29 by danalmei          #+#    #+#             */
/*   Updated: 2024/04/28 21:25:51 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

int	intersect_plane(t_xyz pos, t_xyz pix_dir, t_plane *pl, t_xyz *intersect_pt)
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
	*intersect_pt = add_v(pos, mult_v(pix_dir, t));
	return (1);
}

t_plane	*intersect_planes(t_data *dt, t_xyz pix_dir, t_xyz *intersect_pt)
{
	t_plane		*tmp;
	t_plane		*ret;
	double		min_dist;

	ret = NULL;
	min_dist = INFINITY;
	tmp = dt->plane;
	while (tmp)
	{
		if (intersect_plane(dt->camera->position, pix_dir, tmp, intersect_pt))
		{
			if (distance(dt->camera->position, *intersect_pt) < min_dist)
			{
				min_dist = distance(dt->camera->position, *intersect_pt);
				ret = tmp;
			}
		}
		tmp = tmp->next;
	}
	if (ret)
		intersect_plane(dt->camera->position, pix_dir, ret, intersect_pt);
	return (ret);
}
