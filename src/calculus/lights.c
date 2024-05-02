/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:05:39 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/02 12:55:18 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

t_rgb	base_color(t_data *dt, void *obj, t_type type)
{
	t_ambient	amb;
	t_rgb		start_color;
	t_rgb		base_color;

	amb = *dt->ambient;
	if (type == SPHERE)
		start_color = ((t_sphere *) obj)->color;
	else if (type == PLANE)
		start_color = ((t_plane *) obj)->color;
	else if (type == CYLINDER)
		start_color = ((t_cylinder *) obj)->color;
	base_color.r = (start_color.r * amb.intensity * amb.color.r) / 255;
	base_color.g = (start_color.g * amb.intensity * amb.color.g) / 255;
	base_color.b = (start_color.b * amb.intensity * amb.color.b) / 255;
	return (base_color);
}

void	set_normal(t_xyz *normal, void *obj, t_type type, t_xyz ip)
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

void	set_pos_and_col(t_rgb *col, t_xyz *pos, void *obj, t_type type)
{
	if (type == SPHERE)
	{
		*col = ((t_sphere *) obj)->color;
		*pos = ((t_sphere *) obj)->position;
	}
	else if (type == PLANE)
	{
		*col = ((t_plane *) obj)->color;
		*pos = ((t_plane *) obj)->position;
	}
	else if (type == CYLINDER)
	{
		*col = ((t_cylinder *) obj)->color;
		*pos = ((t_cylinder *) obj)->position;
	}
}

t_rgb	set_color(t_light *lig, t_rgb base_col, double diffuse_intensity)
{
	t_rgb	lit_color;

	lit_color.r = (base_col.r + K_DIFFUSE * lig->color.r * diffuse_intensity);
	lit_color.g = (base_col.g + K_DIFFUSE * lig->color.g * diffuse_intensity);
	lit_color.b = (base_col.b + K_DIFFUSE * lig->color.b * diffuse_intensity);
	lit_color.r = fmin(fmax(lit_color.r, 0), 255);
	lit_color.g = fmin(fmax(lit_color.g, 0), 255);
	lit_color.b = fmin(fmax(lit_color.b, 0), 255);
	return (lit_color);
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
	if (type != PLANE)
		lit_color = add_color(lit_color, specular_light(dt, ip, normal, 10));
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

t_rgb scale_color(t_rgb color, double scale) {
    return (t_rgb){
        fmin(255, color.r * scale),
        fmin(255, color.g * scale),
        fmin(255, color.b * scale)
    };
}

t_rgb add_color(t_rgb color1, t_rgb color2) {
    return (t_rgb){
        fmin(fmax(color1.r + color2.r, 0), 255),
        fmin(fmax(color1.g + color2.g, 0), 255),
        fmin(fmax(color1.b + color2.b, 0), 255)
    };
}
