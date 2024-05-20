/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_intersections_shade.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:51:45 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/20 17:13:27 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

double	solve_t_sp_shade(t_xyz oc, t_xyz pix_dir, double *discr,
	double light_distance)
{
	double	t0;
	double	t1;
	double	temp;
	double	t;

	t0 = -(2.0 * dot(oc, pix_dir)) - sqrt(*discr)
		/ (2 * dot(pix_dir, pix_dir));
	t1 = -(2.0 * dot(oc, pix_dir)) + sqrt(*discr)
		/ (2 * dot(pix_dir, pix_dir));
	if (t0 > t1)
	{
		temp = t0;
		t0 = t1;
		t1 = temp;
	}
	if (t0 > EPSILON && t0 < light_distance)
		t = t0;
	else if (t1 > EPSILON && t1 < light_distance)
		t = t1;
	else
		return (0);
	*discr = t;
	return (1);
}

int	intersect_sphere_shade(t_xyz pos, t_xyz pix_dir, t_sphere *sp, t_xyz *ip)
{
	t_data	*dt;
	t_xyz	oc;
	double	discr;
	double	light_distance;

	dt = data();
	oc = subtr_v(pos, sp->position);
	discr = (2.0 * dot(oc, pix_dir)) * (2.0 * dot(oc, pix_dir)) - 4
		* dot(pix_dir, pix_dir) * (dot(oc, oc)
			- pow(sp->diameter / 2, 2));
	if (discr < 0)
		return (0);
	light_distance = distance(dt->light->position, pos);
	if (!solve_t_sp_shade(oc, pix_dir, &discr, light_distance))
		return (0);
	*ip = add_v(pos, mult_v(pix_dir, discr));
	return (1);
}
