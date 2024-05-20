/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 21:03:07 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/20 16:54:46 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

t_rgb	calculate_color(t_xyz ip, void *obj, t_type type)
{
	t_data	*dt;
	t_rgb	color;
	t_rgb	shadow_col;

	dt = data();
	shadow_col.r = 0;
	shadow_col.g = 0;
	shadow_col.b = 0;
	color = base_color(dt, obj, type);
	if (dt->diffuse_light)
		color = lit_color(dt, ip, obj, type);
	if (dt->hard_shadows)
	{
		if (calc_shadow(dt, ip, obj, type))
			color = shadow_col;
	}
	return (color);
}

int	calc_shadow(t_data *dt, t_xyz ip, void *obj, t_type type)
{
	int		intersect;
	t_xyz	normal;
	t_xyz	shadow_dir;
	t_xyz	shadow_origin;

	intersect = 0;
	set_normal(&normal, obj, type, ip);
	shadow_dir = norm_v(subtr_v(dt->light->position, ip));
	shadow_origin = add_v(ip, mult_v(normal, EPSILON));
	object_intersection2(shadow_dir, &intersect, obj, shadow_origin);
	return (intersect);
}

void	object_intersection2(t_xyz pixel_dir, int *intersec, void *obj,
	t_xyz shadow_origin)
{
	t_xyz	*ip;
	t_data	*dt;

	dt = data();
	ip = ft_safe_malloc(sizeof(t_xyz), data_destroy, NULL);
	if (intersect_shperes2(dt, pixel_dir, ip, shadow_origin))
	{
		if (!intersect_sphere_shade(shadow_origin,
				pixel_dir, (t_sphere *)obj, ip))
			*intersec = 1;
	}
	if (intersect_cylinders2(dt, pixel_dir, ip, shadow_origin))
	{
		if (!intersect_cylinder_shade(shadow_origin,
				pixel_dir, (t_cylinder *)obj, ip))
			*intersec = 1;
	}
	free(ip);
}
