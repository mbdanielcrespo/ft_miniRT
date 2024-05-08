/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:55:52 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/07 16:38:38 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

// TODO: Cam normal is working only along the FOV, not the 360 range, fix it***

int	intersect_sphere_shade(t_xyz pos, t_xyz pix_dir, t_sphere *sp, t_xyz *ip)
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


int intersect_sphere(t_xyz pos, t_xyz pix_dir, t_sphere *sp, t_xyz *ip)
{
    t_xyz oc = subtr_v(pos, sp->position);
    double a = dot(pix_dir, pix_dir);
    double b = 2 * dot(oc, pix_dir);
    double c = dot(oc, oc) - pow(sp->diameter / 2, 2);
    double discr = b * b - 4 * a * c;

    if (discr < 0)
        return 0;

    double sqrt_discr = sqrt(discr);
    double t1 = (-b - sqrt_discr) / (2 * a);
    double t2 = (-b + sqrt_discr) / (2 * a);

    // Choose the smallest t value that is greater than zero
    double t = -1;
    if (t1 > 0 && (t1 < t2 || t2 < 0)) {
        t = t1;
    } else if (t2 > 0) {
        t = t2;
    }

    if (t < 0)
        return 0;  // All intersection points are behind the ray's origin

    *ip = add_v(pos, mult_v(pix_dir, t));
    return 1;
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

// TODO: Check on shading calculus
int	intersect_shperes2(t_data *dt, t_xyz pix_dir, t_xyz *ip)
{
	t_sphere	*tmp;

	tmp = dt->sphere;
	while (tmp)
	{
		if (intersect_sphere_shade(dt->light->position, pix_dir, tmp, ip))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}