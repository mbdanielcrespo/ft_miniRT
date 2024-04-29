/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:55:52 by danalmei          #+#    #+#             */
/*   Updated: 2024/04/29 22:19:03 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

int	intersect_sphere(t_xyz pos, t_xyz pix_dir, t_sphere *sp, t_xyz *ip)
{
	t_xyz	oc;
	double	t;
	double	discr;

	oc = subtr_v(pos, sp->position);
	discr = (2 * dot(oc, pix_dir) * 2 * dot(oc, pix_dir)) 
		- 4 * dot(pix_dir, pix_dir) * (dot(oc, oc) 
			- pow(sp->diameter / 2, 2));
	if (discr < 0)
		return (0);
	t = (-(2 * dot(oc, pix_dir)) - sqrt(discr)) / 
		(2 * dot(pix_dir, pix_dir));
	*ip = add_v(pos, mult_v(pix_dir, t));
	return (1);
}

t_sphere	*intersect_shperes(t_data *dt, t_xyz pix_dir, t_xyz *ip)
{
	t_sphere	*tmp;
	t_sphere	*ret;
	double		min_dist;

	ret = NULL;
	min_dist = INFINITY;
	tmp = dt->sphere;
	while (tmp)
	{
		if (intersect_sphere(dt->camera->position, pix_dir, tmp, ip))
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
		intersect_sphere(dt->camera->position, pix_dir, ret, ip);
	return (ret);
}

int	intersect_shperes2(t_data *dt, t_xyz pix_dir, t_xyz *ip)
{
	t_sphere	*tmp;

	tmp = dt->sphere;
	while (tmp)
	{
		if (intersect_sphere(dt->light->position, pix_dir, tmp, ip))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}