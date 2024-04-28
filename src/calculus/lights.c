/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:05:39 by danalmei          #+#    #+#             */
/*   Updated: 2024/04/28 22:50:33 by danalmei         ###   ########.fr       */
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

t_rgb	lit_color(t_data *dt, t_xyz intersect_pt, void *obj, t_type type)
{
	t_xyz	normal;
	t_rgb	lit_color;
	t_xyz	pos;
	double	diffuse_intensity;

	set_pos_and_col(&lit_color, &pos, obj, type);
	//normal = norm_v(subtr_v(intersect_pt, pos));
	set_normal(&normal, obj, type, intersect_pt);
	diffuse_intensity = fmax(dot(norm_v(normal), 
				norm_v(subtr_v(dt->light->position,
					intersect_pt))), 0) * dt->light->brightness;
	lit_color = set_color(dt->light, lit_color, diffuse_intensity);
	return (lit_color);
}

// Calculate AMBIENT LIGHT (base color) = intensity * initial color 
// Calculate DIFUSE LIGHT (directional light from points)
// Calculate SPECULAR LIGHT (bright spots) = bright spots