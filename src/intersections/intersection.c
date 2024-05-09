/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 21:03:07 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/09 14:07:25 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

// calculate_color(ip, pos, color, type)
// paint_pixel(int pixel, t_rgb color)

t_rgb	calculate_color(t_xyz ip, void *obj, t_type type, t_xyz pix_dir)
{
	t_data	*dt;
	t_rgb	color;
	t_rgb	shadow_col = {0, 0, 0};

	dt = data();
	color = base_color(dt, obj, type);
	if (dt->diffuse_light)
		color = lit_color(dt, ip, obj, type);
	if (dt->hard_shadows)
	{
		if (calc_shadow(dt, ip, obj, type, pix_dir))
			color = shadow_col;
	}
	return (color);
}

int	calc_shadow(t_data *dt, t_xyz ip, void *obj, t_type type, t_xyz pix_dir)
{
	//This function is called when the camera reaches an ip (intersection point) with a object
	//It checks if its goin to be a hardshadow pixel (returns 1 if it is and returns 0 if it isnt)
	
	//Calculate the vector from the ip to the light
	//Check if there is an object in between (if an object is intersected) that isnt its own
	//If there is return 1 else ...
	(void)pix_dir;
	int		intersect = 0;
	t_xyz	normal;
	set_normal(&normal, obj, type, ip);
	t_xyz	shadow_dir = norm_v(subtr_v(dt->light->position, ip));
	t_xyz	shadow_origin = add_v(ip, mult_v(normal, EPSILON));
	
	object_intersection2(dt, shadow_dir, &intersect, obj, type, shadow_origin);
	return (intersect);
}

void	object_intersection2(t_data *dt, t_xyz pixel_dir, int *intersec, void *obj, t_type type, t_xyz shadow_origin)
{
	t_xyz	*ip;

	(void)type;
	ip = ft_safe_malloc(sizeof(t_xyz), data_destroy, NULL);
	if (intersect_shperes2(dt, pixel_dir, ip, shadow_origin))
	{
		if (!intersect_sphere_shade(shadow_origin, pixel_dir, (t_sphere *)obj, ip))
			*intersec = 1;
	}
	if (intersect_cylinders2(dt, pixel_dir, ip, shadow_origin))
	{
		if (!intersect_cylinder(shadow_origin, pixel_dir, (t_cylinder *)obj, ip))
			*intersec = 1;
	}
	free(ip);

	
}

