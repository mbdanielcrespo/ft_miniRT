/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 21:03:07 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/02 14:47:51 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

// calculate_color(ip, pos, color, type)
// paint_pixel(int pixel, t_rgb color)

t_rgb	calculate_color(t_xyz ip, void *obj, t_type type)
{
	t_data	*dt;
	t_rgb	color;
	t_rgb	shadow_col = {0, 0, 0};

	dt = data();
	color = base_color(dt, obj, type);
	color = lit_color(dt, ip, obj, type);
	if (calc_shadow(dt, ip, obj, type))
		color = shadow_col;
	return (color);
}

int	calc_shadow(t_data *dt, t_xyz ip, void *obj, t_type type)
{
	int	intersect;
	t_xyz	ray_dir;
	
	intersect = 0;
	ray_dir = norm_v(subtr_v(dt->light->position, ip));
	object_intersection2(dt, ray_dir, &intersect, obj, type);
	if (intersect)
        return (1);
	return (0);
}

void	object_intersection2(t_data *dt, t_xyz pixel_dir, int *intersec, void *obj, t_type type)
{
	t_xyz	*ip;

	(void)type;

	ip = ft_safe_malloc(sizeof(t_xyz), data_destroy, NULL);
	if (intersect_shperes2(dt, pixel_dir, ip))
	{	
		if (!intersect_sphere_shade(dt->light->position, pixel_dir, (t_sphere *)obj, ip))
			*intersec = 1;
	}
	//if (intersect_planes2(dt, pixel_dir, ip))
	//	*intersec = 1;
	if (intersect_cylinders2(dt, pixel_dir, ip))
	{
		if (!intersect_cylinder(dt->light->position, pixel_dir, (t_cylinder *)obj, ip))
			*intersec = 1;
	}
	free(ip);
}

