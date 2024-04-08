/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 21:03:07 by danalmei          #+#    #+#             */
/*   Updated: 2024/04/08 00:57:03 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

/*
Formula quadratica de interseção da origem O para o centro da esfera C
// Calculo de 
*/
int	intersect_sphere(t_xyz pos, t_xyz pix_dir, t_sphere *sp, t_xyz *intersect_pt)
{
	t_xyz	oc;
	double	t;
	double	a;
	double	b;
	double	c;
	double	discr;
	
	oc = subtractV(pos, *sp->position);
	a = multiplyVs(pix_dir, pix_dir);
	b = 2 * multiplyVs(oc, pix_dir);
	c = multiplyVs(oc, oc) - pow(sp->diameter/2, 2);
	discr = b*b - 4*a*c;
	if (discr < 0)
		return (0);
	t = (-b - sqrt(discr)) / (2*a);
	*intersect_pt = addV(pos, multiplyV(pix_dir, t));
	(void)intersect_pt;
	//print_trpl_float(&intersect_pt);
	//printf("\n");
	return (1);	
}

void	object_intersections(t_data *dt, t_xyz pixel_dir, int pixel)
{
	t_rgb	base_col;
	t_xyz	*intersect_pt;	// MALLOC
	
	intersect_pt = ft_safe_malloc(sizeof(t_xyz), data_destroy, NULL);
	// Intersect SPHERES
	if (intersect_sphere(*dt->camera->position, pixel_dir, dt->sphere, intersect_pt))
	{
		base_col = base_color(dt, *dt->sphere->color);
		dt->img.img_data[pixel + 0] = base_col.b;
		dt->img.img_data[pixel + 1] = base_col.g;
		dt->img.img_data[pixel + 2] = base_col.r;
	}
	else
	{
		dt->img.img_data[pixel + 0] = 255;
		dt->img.img_data[pixel + 1] = 255;
		dt->img.img_data[pixel + 2] = 255;
	}
	free(intersect_pt);
	// Intersect CYLINDERS
	// Intersect PLANES
}