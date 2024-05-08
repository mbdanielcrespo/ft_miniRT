/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:18:50 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/07 16:35:26 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

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
	intersec = 0;
	return (0);
}

void	object_intersections(t_data *dt, t_xyz pixel_dir, int pixel, int intersec)
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
