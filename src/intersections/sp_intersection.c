/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:55:52 by danalmei          #+#    #+#             */
/*   Updated: 2024/04/18 15:05:39 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

int	intersect_sphere(t_xyz pos, t_xyz pix_dir, t_sphere *sp, t_xyz *intersect_pt)
{
	t_xyz	oc;
	double	t;
	double	discr;
	
	oc = subtrV(pos, *sp->position);
	discr = (2 * dot(oc, pix_dir) * 2 * dot(oc, pix_dir)) 
			- 4 * dot(pix_dir, pix_dir) * (dot(oc, oc) 
			- pow(sp->diameter/2, 2));
	if (discr < 0)
		return (0);
	t = (-(2 * dot(oc, pix_dir)) - sqrt(discr)) / 
		(2 * dot(pix_dir, pix_dir));
	*intersect_pt = addV(pos, multV(pix_dir, t));
	return (1);	
}

t_sphere	*intersect_shperes(t_data *dt, t_xyz pix_dir, t_xyz *intersect_pt)
{
	t_sphere	*tmp;
	t_sphere	*ret;
	double		min_dist;

	ret = NULL;
	min_dist = INFINITY;
	tmp = dt->sphere;
	while (tmp)
	{
		if (intersect_sphere(*dt->camera->position, pix_dir, tmp, intersect_pt))
		{
			if (distance(*dt->camera->position, *intersect_pt) < min_dist)
			{
				min_dist = distance(*dt->camera->position, *intersect_pt);
				ret = tmp;
			}
		}
		tmp = tmp->next;
	}
	if (ret)
		intersect_sphere(*dt->camera->position, pix_dir, ret, intersect_pt);
	return (ret);
}
