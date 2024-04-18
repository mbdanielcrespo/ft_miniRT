/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 21:03:07 by danalmei          #+#    #+#             */
/*   Updated: 2024/04/18 15:12:54 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

// calculate_color(intersect_pt, pos, color, type)
// paint_pixel(int pixel, t_rgb color)

t_rgb	calculate_color(t_rgb obj_color, t_xyz *ip, t_xyz *pos)
{
	t_data	*dt;
	t_rgb	color;

	dt = data();
	color = base_color(dt, obj_color);
	color = lit_color(dt, color, ip, pos);
	// other light
	return (color);
}

void	paint_pixel(int pixel, t_rgb color, int color_flag)
{
	t_data	*dt;
	
	dt = data();
	if (color_flag)
	{
		dt->img.img_data[pixel + 0] = color.b;
		dt->img.img_data[pixel + 1] = color.g;
		dt->img.img_data[pixel + 2] = color.r;
	}
	else
	{
		dt->img.img_data[pixel + 0] = 0;
		dt->img.img_data[pixel + 1] = 0;
		dt->img.img_data[pixel + 2] = 0;
	}
}

void	object_intersections(t_data *dt, t_xyz pixel_dir, int pixel)
{
	t_xyz		*intersect_pt;	// MALLOC
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
	t_rgb	color;
	double	min_dist;
	double	dist;
	
	sp = NULL;
	pl = NULL;
	cy = NULL;
	dist = 0;
	min_dist = INFINITY;
	intersect_pt = ft_safe_malloc(sizeof(t_xyz), data_destroy, NULL);
	sp = intersect_shperes(dt, pixel_dir, intersect_pt);
	if (sp)
	{
		dist = distance(*dt->camera->position, *intersect_pt);
		if (dist < min_dist)
		{
			color = calculate_color(*sp->color, intersect_pt, sp->position);
			paint_pixel(pixel, color, 1);
		}
	}
	pl = intersect_planes(dt, pixel_dir, intersect_pt);
	if (pl)
	{
		dist = distance(*dt->camera->position, *intersect_pt);
		if (dist < min_dist)
		{
			color = calculate_color(*pl->color, intersect_pt, pl->position);
			paint_pixel(pixel, color, 1);
		}
	}
	cy = intersect_cylinders(dt, pixel_dir, intersect_pt);
	if (cy)
	{
		dist = distance(*dt->camera->position, *intersect_pt);
		if (dist < min_dist)
		{
			color = calculate_color(*cy->color, intersect_pt, cy->position);
			paint_pixel(pixel, color, 1);
		}
	}
	
	free(intersect_pt);
}
