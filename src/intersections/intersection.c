/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 21:03:07 by danalmei          #+#    #+#             */
/*   Updated: 2024/04/29 22:24:23 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

// calculate_color(ip, pos, color, type)
// paint_pixel(int pixel, t_rgb color)

t_rgb	calculate_color(t_xyz ip, void *obj, t_type type)
{
	t_data	*dt;
	t_rgb	color;

	dt = data();
	color = base_color(dt, obj, type);
	color = lit_color(dt, ip, obj, type);
	color = calc_shadow(dt, ip, color);
	return (color);
}

void	paint_pixel(int pixel, t_rgb color, int color_flag)
{
	t_data	*dt;

	dt = data();
	if (color_flag != 0)
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

int	update_dist(void *obj, t_xyz *ip, double *min_dist, int *intersec)
{
	t_data	*dt;
	double	dist;

	dt = data();
	if (obj)
	{
		dist = distance(dt->camera->position, *ip);
		if (dist < *min_dist)
		{
			*intersec = 1;
			*min_dist = dist;
			return (1);
		}
	}
	return (0);
}

t_rgb	calc_shadow(t_data *dt, t_xyz ip, t_rgb color)
{
	int	intersect;
	t_xyz	ray_dir;
	t_rgb	shadow_col = {0, 0, 0};
	
	intersect = 0;
	ray_dir = norm_v(subtr_v(dt->light->position, ip));
	object_intersection2(dt, ray_dir, &intersect);
	if (intersect)
        return (shadow_col);
	return (color);
}

void	object_intersection2(t_data *dt, t_xyz pixel_dir, int *intersec)
{
	t_xyz	*ip;
	

	ip = ft_safe_malloc(sizeof(t_xyz), data_destroy, NULL);
	if (intersect_shperes2(dt, pixel_dir, ip))
		*intersec = 1;
	if (intersect_planes2(dt, pixel_dir, ip))
		*intersec = 1;
	if (intersect_cylinders2(dt, pixel_dir, ip))
		*intersec = 1;
	free(ip);
}

void	object_intersections(t_data *dt, t_xyz pixel_dir,
								int pixel, int intersec)
{
	t_xyz	*ip;
	t_rgb	color;
	void	*obj;
	double	min_dist;

	obj = NULL;
	min_dist = INFINITY;
	intersec = 0;
	ip = ft_safe_malloc(sizeof(t_xyz), data_destroy, NULL);
	obj = intersect_shperes(dt, pixel_dir, ip);
	if (update_dist(obj, ip, &min_dist, &intersec))
		color = calculate_color(*ip, obj, SPHERE);
	obj = intersect_planes(dt, pixel_dir, ip);
	if (update_dist(obj, ip, &min_dist, &intersec))
		color = calculate_color(*ip, obj, PLANE);
	obj = intersect_cylinders(dt, pixel_dir, ip);
	if (update_dist(obj, ip, &min_dist, &intersec))
		color = calculate_color(*ip, obj, CYLINDER);
	if (intersec != 0)
		paint_pixel(pixel, color, 1);
	else
		paint_pixel(pixel, color, 0);
	free(ip);
}
