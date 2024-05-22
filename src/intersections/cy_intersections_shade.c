/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_intersections_shade.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:57:19 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/22 13:45:46 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

int	solve_t_shade(t_xyz d_perp, t_xyz co_perp, double *discr,
	double light_distance)
{
	double	t0;
	double	t1;
	double	t;
	double	temp;

	t0 = (-(2 * dot(d_perp, co_perp)) - sqrt(*discr))
		/ (2 * dot(d_perp, d_perp));
	t1 = (-(2 * dot(d_perp, co_perp)) + sqrt(*discr))
		/ (2 * dot(d_perp, d_perp));
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

int	solve_cylinder_shade(t_xyz pos, t_xyz pix_dir, t_cylinder *cy, t_xyz *ip)
{
	t_xyz	v;
	t_xyz	d_perp;
	t_xyz	co_perp;
	double	light_distance;
	double	discr;

	v = norm_v(cy->norm_vect);
	d_perp = subtr_v(pix_dir, mult_v(v, dot(pix_dir, v)));
	co_perp = subtr_v(subtr_v(pos, cy->position),
			mult_v(v, dot(subtr_v(pos, cy->position), v)));
	discr = pow((2 * dot(d_perp, co_perp)), 2) - 4 * dot(d_perp, d_perp)
		* (dot(co_perp, co_perp) - pow(cy->diameter / 2, 2));
	if (discr < 0)
		return (0);
	light_distance = distance((*data()).light->position, pos);
	if (!solve_t_shade(d_perp, co_perp, &discr, light_distance))
		return (0);
	*ip = add_v(pos, mult_v(pix_dir, discr));
	return (1);
}

int	intersect_cylinder_shade(t_xyz pos, t_xyz pix_dir, t_cylinder *cy,
	t_xyz *ip)
{
	t_plane	pl1;
	t_plane	pl2;
	int		ret;
	double	min_dist;

	ret = 0;
	min_dist = INFINITY;
	pl1.norm_vect = cy->norm_vect;
	pl1.position = add_v(cy->position,
			mult_v(cy->norm_vect, cy->height / 2.0));
	pl2.norm_vect = mult_v(cy->norm_vect, -1);
	pl2.position = subtr_v(cy->position,
			mult_v(cy->norm_vect, cy->height / 2.0));
	if (intersect_plane_shade(pos, pix_dir, &pl1, ip)
		&& within_cylinder_radius(ip, cy, pl1.position, &min_dist))
		ret = 1;
	if (intersect_plane_shade(pos, pix_dir, &pl2, ip)
		&& within_cylinder_radius(ip, cy, pl2.position, &min_dist))
		ret = 1;
	if (solve_cylinder_shade(pos, pix_dir, cy, ip) && 
		within_cylinder_tube(cy, ip, &min_dist))
		ret = 1;
	return (ret);
}

t_cylinder	*intersect_cylinders(t_data *dt, t_xyz pix_dir, t_xyz *ip)
{
	t_cylinder	*tmp;
	t_cylinder	*ret;
	double		min_dist;

	ret = NULL;
	min_dist = INFINITY;
	tmp = dt->cylinder;
	while (tmp)
	{
		if (intersect_cylinder(dt->camera->position, pix_dir, tmp, ip))
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
		intersect_cylinder(dt->camera->position, pix_dir, ret, ip);
	return (ret);
}

int	intersect_cylinders2(t_data *dt, t_xyz pix_dir, t_xyz *ip,
	t_xyz shadow_origin)
{
	t_cylinder	*tmp;

	tmp = dt->cylinder;
	while (tmp)
	{
		if (intersect_cylinder_shade(shadow_origin, pix_dir, tmp, ip))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
