/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:05:39 by danalmei          #+#    #+#             */
/*   Updated: 2024/04/26 15:14:32 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

t_rgb	base_color(t_data *dt, void *obj, t_type type)
{
	t_ambient	A;
	t_rgb		start_color;
	t_rgb		base_color;
		
	A = *dt->ambient;
	if (type == SPHERE)
		start_color = ((t_sphere*)obj)->color;
	else if (type == PLANE)
		start_color = ((t_plane*)obj)->color;
	else if (type == CYLINDER)
		start_color = ((t_cylinder*)obj)->color;
	base_color.r  = (start_color.r * A.intensity * A.color.r) / 255;
	base_color.g  = (start_color.g * A.intensity * A.color.g) / 255;
	base_color.b  = (start_color.b * A.intensity * A.color.b) / 255;
	return (base_color);
}

void	set_normal(t_xyz *normal, void *obj, t_type type, t_xyz ip)
{
	if (type == SPHERE)
		*normal = normV(subtrV(ip, ((t_sphere*)obj)->position));
	else if (type == PLANE)
		*normal = ((t_plane*)obj)->norm_vect;
	else if (type == CYLINDER)
	{
		t_xyz center_to_point = subtrV(ip, ((t_cylinder*)obj)->position);
    	t_xyz normalized_axis = normV(((t_cylinder*)obj)->norm_vect);
		double projection_length = dot(center_to_point, normalized_axis);
    	t_xyz projection = multV(normalized_axis, projection_length);
		t_xyz closest_point_on_axis = addV(((t_cylinder*)obj)->position, projection);
		*normal = normV(subtrV(ip, closest_point_on_axis));
	}
}

void	set_pos_and_col(t_rgb *col, t_xyz *pos, void *obj, t_type type)
{
	if (type == SPHERE)
	{
		*col = ((t_sphere*)obj)->color;
		*pos = ((t_sphere*)obj)->position;
	}
	else if (type == PLANE)
	{
		*col = ((t_plane*)obj)->color;
		*pos = ((t_plane*)obj)->position;
	}
	else if (type == CYLINDER)
	{
		*col = ((t_cylinder*)obj)->color;
		*pos = ((t_cylinder*)obj)->position;
	}
}

t_rgb	lit_color(t_data *dt, t_xyz intersect_pt, void *obj, t_type type)
{
	t_light	*L;
	t_rgb	lit_color;
	t_xyz	light_dir;
	t_xyz	normal;
	
	t_rgb	base_col;
	t_xyz	pos;
	double dotNL, diffuse_intensity;

	L = dt->light;
	set_pos_and_col(&base_col, &pos, obj, type);
	//normal = normV(subtrV(intersect_pt, pos));
	set_normal(&normal, obj, type, intersect_pt);
	light_dir = normV(subtrV(L->position, intersect_pt));
	dotNL = dot(normV(normal), light_dir);
	dotNL = fmax(dotNL, 0);
	diffuse_intensity = dotNL * L->brightness;
	lit_color.r = (base_col.r + K_DIFFUSE * L->color.r * diffuse_intensity);
	lit_color.g = (base_col.g + K_DIFFUSE * L->color.g * diffuse_intensity);
	lit_color.b = (base_col.b + K_DIFFUSE * L->color.b * diffuse_intensity);
	lit_color.r = fmin(fmax(lit_color.r, 0), 255);
    lit_color.g = fmin(fmax(lit_color.g, 0), 255);
    lit_color.b = fmin(fmax(lit_color.b, 0), 255);
	return (lit_color);
}

// Calculate AMBIENT LIGHT (base color) = intensity * initial color 
// Calculate DIFUSE LIGHT (directional light from points)
// Calculate SPECULAR LIGHT (bright spots) = bright spots