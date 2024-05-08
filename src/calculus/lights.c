/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:05:39 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/08 16:02:13 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

void	set_normal(t_xyz *normal, void *obj, t_type type, t_xyz ip) //, int on_base)
{
	t_xyz	normalized_axis;
	t_xyz	projection;
	double	projection_length;

	if (type == SPHERE)
		*normal = norm_v(subtr_v(ip, ((t_sphere *) obj)->position));
	else if (type == PLANE)
		*normal = ((t_plane *) obj)->norm_vect;
	else if (type == CYLINDER)
	{
		normalized_axis = norm_v(((t_cylinder *) obj)->norm_vect);
		projection_length = dot(subtr_v(ip, ((t_cylinder *) obj)->position),
					normalized_axis);
		projection = mult_v(normalized_axis, projection_length);
		*normal = norm_v(subtr_v(ip, add_v(((t_cylinder *) obj)->position,
						projection)));
	}
}

t_rgb	lit_color(t_data *dt, t_xyz ip, void *obj, t_type type)
{
	t_xyz	normal;
	t_rgb	lit_color;
	t_xyz	pos;
	double	diffuse_intensity;

	set_pos_and_col(&lit_color, &pos, obj, type);
	set_normal(&normal, obj, type, ip);
	diffuse_intensity = fmax(dot(norm_v(normal), 
				norm_v(subtr_v(dt->light->position,
					ip))), 0) * dt->light->brightness;
	lit_color = set_color(dt->light, lit_color, diffuse_intensity);
	if (dt->specular_light)
	{
		if (type != PLANE)
			lit_color = add_color(lit_color, specular_light(dt, ip, normal, 10));
	}
	return (lit_color);
}

t_rgb specular_light(t_data *dt, t_xyz ip, t_xyz normal, double shininess)
{
    t_xyz view_dir = norm_v(subtr_v(dt->camera->position, ip));
    t_xyz light_dir = norm_v(subtr_v(dt->light->position, ip));
    t_xyz reflect_dir = reflect_v(light_dir, normal);
    double spec_intensity = pow(fmax(dot(view_dir, reflect_dir), 0), shininess);
    t_rgb specular_color = scale_color(dt->light->color, spec_intensity * dt->light->brightness);
    return specular_color;
}

t_xyz reflect_v(t_xyz light_dir, t_xyz normal)
{
    double dot_product = dot(light_dir, normal);
    t_xyz reflected = {
        2 * dot_product * normal.x - light_dir.x,
        2 * dot_product * normal.y - light_dir.y,
        2 * dot_product * normal.z - light_dir.z
    };
    return reflected;
}

