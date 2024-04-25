/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:05:39 by danalmei          #+#    #+#             */
/*   Updated: 2024/04/25 15:56:15 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

t_rgb	base_color(t_data *dt, t_rgb starting_col)
{
	t_ambient	A;
	t_rgb		base_color;
	
	
	// TODO: ERROR IF AMBIENT IS >1
	A = *dt->ambient;
	base_color.r  = (starting_col.r * A.intensity * A.color.r) / 255;
	base_color.g  = (starting_col.g * A.intensity * A.color.g) / 255;
	base_color.b  = (starting_col.b * A.intensity * A.color.b) / 255;
	// Take in consideration color value for ambient light ***
	//printf("Calculated base color:\n");
	//print_trpl_int(base_color);
	return (base_color);
}

t_rgb	lit_color(t_data *dt, t_rgb base_col, t_xyz intersect_pt, t_xyz pos)
{
	t_light	*L;
	t_rgb	lit_color;
	t_xyz	light_dir;
	t_xyz	normal;
	double dotNL, diffuse_intensity;

	L = dt->light;
	normal = normV(subtrV(intersect_pt, pos));
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