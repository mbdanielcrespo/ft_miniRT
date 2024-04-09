/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 21:03:07 by danalmei          #+#    #+#             */
/*   Updated: 2024/04/09 14:09:42 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

/*
void	interect_planes(t_data *dt, t_xyz pix_dir, t_xyz *intersect_pt)
{
	t_plane		*tmp;
	int			min_dist;
	int			distance;
	
	tmp = dt->plane;
	while (tmp)
	{
		distance = intersect_plane();
		if (distance < min_dist)
		{
			paint_pixel(distance, intersect_pt, *dt->plane->color);
			min_dist = distance;
		}
		tmp = tmp->next;
	}
	
}
*/

/*
void	intersect_shperes(t_data *dt, t_xyz pix_dir, t_xyz *intersect_pt)
{
	t_sphere	*tmp;
	int			min_dist;
	int			distance;

	distance = 0;
	min_dist = __INT_MAX__;
	tmp = dt->sphere;
	while (tmp)
	{
		distance = intersect_sphere(*dt->camera->position, pix_dir, tmp, intersect_pt);
		if (distance < min_dist)
		{
			paint_pixel(distance, intersect_pt, *dt->sphere->color);
			min_dist = distance;
		}
		tmp = tmp->next;
	}
}*/

/*
	a = multiplyVs(pix_dir, pix_dir);
	b = 2 * multiplyVs(oc, pix_dir);
	c = multiplyVs(oc, oc) - pow(sp->diameter/2, 2);
*/
int	intersect_sphere(t_xyz pos, t_xyz pix_dir, t_sphere *sp, t_xyz *intersect_pt)
{
	t_xyz	oc;
	double	t;
	double	discr;
	
	oc = subtractV(pos, *sp->position);
	discr = (2 * multiplyVs(oc, pix_dir) * 2 * multiplyVs(oc, pix_dir)) 
			- 4 * multiplyVs(pix_dir, pix_dir) * (multiplyVs(oc, oc) 
			- pow(sp->diameter/2, 2));
	if (discr < 0)
		return (0);
	t = (-(2 * multiplyVs(oc, pix_dir)) - sqrt(discr)) / 
		(2 * multiplyVs(pix_dir, pix_dir));
	*intersect_pt = addV(pos, multiplyV(pix_dir, t));
	return (1);	
}

int	intersect_plane(t_xyz pos, t_xyz pix_dir, t_plane *pl, t_xyz *intersect_pt)
{
	double	dotND;
	t_xyz	vecOP;
	double	t;

	dotND = multiplyVs(*pl->norm_vect, pix_dir);
	if (fabs(dotND) < 1e-6)
		return (0);
	vecOP = subtractV(*pl->position, pos);
	t = multiplyVs(vecOP, *pl->norm_vect) / dotND;
	if (t < 0)
		return (0);
	*intersect_pt = addV(pos, multiplyV(pix_dir, t));
	return (1);
}

void	object_intersections(t_data *dt, t_xyz pixel_dir, int pixel)
{
	t_rgb	color;
	t_xyz	*intersect_pt;	// MALLOC
	
	intersect_pt = ft_safe_malloc(sizeof(t_xyz), data_destroy, NULL);
	if (intersect_shpere(*dt->camera->position, pixel_dir, dt->plane, intersect_pt))
	{
		color = base_color(dt, *dt->sphere->color); // dt->obj->color
		color = lit_color_sp(dt, color, intersect_pt, dt->sphere); // dt->obj->pos
		dt->img.img_data[pixel + 0] = color.b;
		dt->img.img_data[pixel + 1] = color.g;
		dt->img.img_data[pixel + 2] = color.r;
	}
	else
	{
		dt->img.img_data[pixel + 0] = 255;
		dt->img.img_data[pixel + 1] = 255;
		dt->img.img_data[pixel + 2] = 255;
	}
	free(intersect_pt);
	// Intersect CYLINDERS
	// Intersect PLANES
}

/*
void	paint_pixel(int value, t_xyz intersect_pt, t_rgb obj_color)
{
	t_rgb	color;
	
	if (value)
	{
		color = base_color(dt, obj_color);
		color = lit_color_sp(dt, color, intersect_pt, dt->sphere);
		dt->img.img_data[pixel + 0] = color.b;
		dt->img.img_data[pixel + 1] = color.g;
		dt->img.img_data[pixel + 2] = color.r;
	}
	else
	{
		dt->img.img_data[pixel + 0] = 255;
		dt->img.img_data[pixel + 1] = 255;
		dt->img.img_data[pixel + 2] = 255;
	}
}*/