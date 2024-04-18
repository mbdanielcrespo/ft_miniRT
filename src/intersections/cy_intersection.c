/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:41:13 by danalmei          #+#    #+#             */
/*   Updated: 2024/04/18 15:06:38 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

int	within_cylinder_radius(t_xyz *intersect_pt, t_cylinder *cy, t_xyz *cap_center)
{
	double	dist;
	
	dist = distance(*intersect_pt, *cap_center);
	if (dist <= (cy->diameter / 2.0))
		return (1);
	return (0);
}

int within_cylinder_tube(t_cylinder *cy, t_xyz *intersect_pt)
{
	t_xyz norm_dir;
	t_xyz center_to_point;
	double deform_fact;
	double proj_length;
	
	norm_dir = normV(*(cy->norm_vect));
	center_to_point = subtrV(*intersect_pt, *(cy->position));
	proj_length = dot(center_to_point, norm_dir);
	deform_fact = fabs((double)norm_dir.x) + fabs((double)norm_dir.y) + fabs((double)norm_dir.z);
	if (deform_fact < 1e-6)
		deform_fact = 1;
	if (fabs(proj_length) <= ((cy->height / 2.0) * deform_fact))
		return (1);
	return (0);
}

int solve_cylinder(t_xyz pos, t_xyz pix_dir, t_cylinder *cy, t_xyz *intersect_pt)
{
	t_xyz V = normV(*cy->norm_vect);
	t_xyz D_perp = subtrV(pix_dir, multV(V, dot(pix_dir, V)));
	t_xyz CO_perp = subtrV(subtrV(pos, *cy->position), multV(V, dot(subtrV(pos, *cy->position), V)));

	double A = dot(D_perp, D_perp);
	double B = 2 * dot(D_perp, CO_perp);
	double C = dot(CO_perp, CO_perp) - pow(cy->diameter/2, 2);
	double discriminant = pow(B, 2) - 4 * A * C;
	if (discriminant < 0)
		return 0;
	double sqrtDiscriminant = sqrt(discriminant);
	double t0 = (-B - sqrtDiscriminant) / (2 * A);
	double t1 = (-B + sqrtDiscriminant) / (2 * A);

	if (t0 > t1) { double temp = t0; t0 = t1; t1 = temp; }

	double t = (t0 >= 0) ? t0 : ((t1 >= 0) ? t1 : -1);
	if (t < 0)
		return 0;	
	*intersect_pt = addV(pos, multV(pix_dir, t));
	return 1;
}

int	intersect_cylinder(t_xyz pos, t_xyz pix_dir, t_cylinder *cy, t_xyz *intersect_pt)
{
	t_plane pl1;
	t_plane	pl2;
	int		ret;
	
	ret = 0;
	pl1.norm_vect = ft_safe_malloc(sizeof(t_xyz), data_destroy, NULL);
	pl1.position = ft_safe_malloc(sizeof(t_xyz), data_destroy, NULL);
	pl2.norm_vect = ft_safe_malloc(sizeof(t_xyz), data_destroy, NULL);
	pl2.position = ft_safe_malloc(sizeof(t_xyz), data_destroy, NULL);
	*pl1.norm_vect = *cy->norm_vect;
	*pl1.position = addV(*cy->position, multV(*cy->norm_vect, cy->height / 2.0));
	*pl2.norm_vect = multV(*cy->norm_vect, -1);
	*pl2.position = subtrV(*cy->position, multV(*cy->norm_vect, cy->height / 2.0));
	if (intersect_plane(pos, pix_dir, &pl1, intersect_pt) && within_cylinder_radius(intersect_pt, cy, pl1.position))
		ret = 1;
	if (intersect_plane(pos, pix_dir, &pl2, intersect_pt) && within_cylinder_radius(intersect_pt, cy, pl2.position))
		ret = 1;
	if (solve_cylinder(pos, pix_dir, cy, intersect_pt) && within_cylinder_tube(cy, intersect_pt))
		ret = 1;
	free(pl1.norm_vect);
	free(pl1.position);
	free(pl2.norm_vect);
	free(pl2.position);
	return (ret);
}

t_cylinder	*intersect_cylinders(t_data *dt, t_xyz pix_dir, t_xyz *intersect_pt)
{
	t_cylinder	*tmp;
	t_cylinder	*ret;
	double		min_dist;

	ret = NULL;
	min_dist = INFINITY;
	tmp = dt->cylinder;
	while (tmp)
	{
		if (intersect_cylinder(*dt->camera->position, pix_dir, tmp, intersect_pt))
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
		intersect_cylinder(*dt->camera->position, pix_dir, ret, intersect_pt);
	return (ret);
}
