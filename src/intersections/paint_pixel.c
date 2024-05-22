/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 21:03:07 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/22 12:11:40 by danalmei         ###   ########.fr       */
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

