/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:52:25 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/08 15:58:19 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

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

t_rgb scale_color(t_rgb color, double scale)
{
    return (t_rgb){
        fmin(255, color.r * scale),
        fmin(255, color.g * scale),
        fmin(255, color.b * scale)
    };
}

t_rgb add_color(t_rgb color1, t_rgb color2)
{
    return (t_rgb){
        fmin(fmax(color1.r + color2.r, 0), 255),
        fmin(fmax(color1.g + color2.g, 0), 255),
        fmin(fmax(color1.b + color2.b, 0), 255)
    };
}