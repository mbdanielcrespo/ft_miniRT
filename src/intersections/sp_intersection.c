/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:55:52 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/20 16:51:59 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

// TODO: Cam normal is working only along the FOV, not the 360 range, fix it***

double	solve_t_sp(t_xyz oc, t_xyz pix_dir, double *discr)
{
	double	t0;
	double	t1;
	double	t;
	double	temp;

	t0 = (-(2.0 * dot(oc, pix_dir)) - sqrt(*discr))
		/ (2 * dot(pix_dir, pix_dir));
	t1 = (-(2.0 * dot(oc, pix_dir)) + sqrt(*discr))
		/ (2 * dot(pix_dir, pix_dir));
	if (t0 > t1)
	{
		temp = t0;
		t0 = t1;
		t1 = temp;
	}
	if (t0 >= 0)
		t = t0;
	else if (t1 >= 0)
		t = t1;
	else
		t = -1;
	if (t < 0)
		return (0);
	*discr = t;
	return (1);
}

int	intersect_sphere(t_xyz pos, t_xyz pix_dir, t_sphere *sp, t_xyz *ip)
{
	t_xyz	oc;
	double	discr;

	oc = subtr_v(pos, sp->position);
	discr = (2 * dot(oc, pix_dir) * 2 * dot(oc, pix_dir)) 
		- 4 * dot(pix_dir, pix_dir) * (dot(oc, oc) 
			- pow(sp->diameter / 2, 2));
	if (discr < 0)
		return (0);
	if (!solve_t_sp(oc, pix_dir, &discr))
		return (0);
	*ip = add_v(pos, mult_v(pix_dir, discr));
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
		if (intersect_sphere(dt->camera->position, pix_dir, tmp, ip) == 1)
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

int	intersect_shperes2(t_data *dt, t_xyz pix_dir, t_xyz *ip, t_xyz shadow_orign)
{
	t_sphere	*tmp;

	tmp = dt->sphere;
	while (tmp)
	{
		if (intersect_sphere_shade(shadow_orign, pix_dir, tmp, ip))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
