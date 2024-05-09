/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:55:52 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/09 13:43:10 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

// TODO: Cam normal is working only along the FOV, not the 360 range, fix it***

int intersect_sphere_shade(t_xyz pos, t_xyz pix_dir, t_sphere *sp, t_xyz *ip) {
	t_data	*dt = data();
    t_xyz oc = subtr_v(pos, sp->position);
    double a = dot(pix_dir, pix_dir);
    double b = 2.0 * dot(oc, pix_dir);
    double c = dot(oc, oc) - pow(sp->diameter / 2, 2);
    double discr = b * b - 4 * a * c;

    if (discr < 0) {
        return 0;  // No intersection if discriminant is negative
    }

    double sqrt_discr = sqrt(discr);
    double t0 = (-b - sqrt_discr) / (2 * a);
    double t1 = (-b + sqrt_discr) / (2 * a);

    // Ensure t0 is the smaller value
    if (t0 > t1) {
        double temp = t0;
        t0 = t1;
        t1 = temp;
    }

    double light_distance = distance(dt->light->position, pos);

    // Only consider t0 if it's within the valid range
    if (t0 > EPSILON && t0 < light_distance) {
        *ip = add_v(pos, mult_v(pix_dir, t0));
        return 1;
    }

    // Check t1 only if t0 is invalid
    if (t1 > EPSILON && t1 < light_distance) {
        *ip = add_v(pos, mult_v(pix_dir, t1));
        return 1;
    }

    return 0;  // No valid intersections
}

int intersect_sphere(t_xyz pos, t_xyz pix_dir, t_sphere *sp, t_xyz *ip)
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