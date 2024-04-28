/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:41:13 by danalmei          #+#    #+#             */
/*   Updated: 2024/04/28 22:22:26 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

int	within_cylinder_radius(t_xyz *ip, t_cylinder *cy, t_xyz cap_center)
{
	double	dist;

	dist = distance(*ip, cap_center);
	if (dist <= (cy->diameter / 2.0))
		return (1);
	return (0);
}

int	within_cylinder_tube(t_cylinder *cy, t_xyz *ip)
{
	t_xyz	norm_dir;
	t_xyz	center_to_point;
	double	deform_fact;
	double	proj_length;

	norm_dir = norm_v(cy->norm_vect);
	center_to_point = subtr_v(*ip, cy->position);
	proj_length = dot(center_to_point, norm_dir);
	deform_fact = fabs((double)norm_dir.x) + fabs((double)norm_dir.y) + 
		fabs((double)norm_dir.z);
	if (deform_fact < 1e-6)
		deform_fact = 1;
	if (fabs(proj_length) <= ((cy->height / 2.0) * deform_fact))
		return (1);
	return (0);
}

int	solve_t(t_xyz d_perp, t_xyz co_perp, double *discr)
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

int	solve_cylinder(t_xyz pos, t_xyz pix_dir, t_cylinder *cy, t_xyz *ip)
{
	t_xyz	v;
	t_xyz	d_perp;
	t_xyz	co_perp;
	double	discr;

	v = norm_v(cy->norm_vect);
	d_perp = subtr_v(pix_dir, mult_v(v, dot(pix_dir, v)));
	co_perp = subtr_v(subtr_v(pos, cy->position),
			mult_v(v, dot(subtr_v(pos, cy->position), v)));
	discr = pow((2 * dot(d_perp, co_perp)), 2) - 4 * dot(d_perp, d_perp)
		* (dot(co_perp, co_perp) - pow(cy->diameter / 2, 2));
	if (discr < 0)
		return (0);
	if (!solve_t(d_perp, co_perp, &discr))
		return (0);
	*ip = add_v(pos, mult_v(pix_dir, discr));
	return (1);
}

int	intersect_cylinder(t_xyz pos, t_xyz pix_dir, t_cylinder *cy, t_xyz *ip)
{
	t_plane	*pl1;
	t_plane	*pl2;
	int		ret;

	ret = 0;
	pl1 = ft_safe_malloc(sizeof(t_plane), data_destroy, NULL);
	pl2 = ft_safe_malloc(sizeof(t_plane), data_destroy, NULL);
	pl1->norm_vect = cy->norm_vect;
	pl1->position = add_v(cy->position,
			mult_v(cy->norm_vect, cy->height / 2.0));
	pl2->norm_vect = mult_v(cy->norm_vect, -1);
	pl2->position = subtr_v(cy->position,
			mult_v(cy->norm_vect, cy->height / 2.0));
	if (intersect_plane(pos, pix_dir, pl1, ip)
		&& within_cylinder_radius(ip, cy, pl1->position))
		ret = 1;
	if (intersect_plane(pos, pix_dir, pl2, ip)
		&& within_cylinder_radius(ip, cy, pl2->position))
		ret = 1;
	if (solve_cylinder(pos, pix_dir, cy, ip) && 
		within_cylinder_tube(cy, ip))
		ret = 1;
	free(pl1);
	free(pl2);
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
