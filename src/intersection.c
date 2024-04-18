/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 21:03:07 by danalmei          #+#    #+#             */
/*   Updated: 2024/04/17 22:12:23 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

/*
void	interect_planes(t_data *dt, t_xyz pix_dir, t_xyz *intersect_pt)
{
	t_plane		*tmp;
	int			min_dist;
	int			distance;
	
	tmp = dt->plane;
	while (tmp)
	{
		distance = intersect_plane();
		if (distance < min_dist)
		{
			paint_pixel(distance, intersect_pt, *dt->plane->color);
			min_dist = distance;
		}
		tmp = tmp->next;
	}	
}

void	intersect_shperes(t_data *dt, t_xyz pix_dir, t_xyz *intersect_pt)
{
	t_sphere	*tmp;
	int			min_dist;
	int			distance;

	distance = 0;
	min_dist = INFINITY;
	tmp = dt->sphere;
	while (tmp)
	{
		distance = intersect_sphere(*dt->camera->position, pix_dir, tmp, intersect_pt);
		if (distance < min_dist)
		{
			paint_pixel(distance, intersect_pt, *dt->sphere->color);
			min_dist = distance;
		}
		tmp = tmp->next;
	}
}*/

/*
a = multiplyVs(pix_dir, pix_dir);
b = 2 * multiplyVs(oc, pix_dir);
c = multiplyVs(oc, oc) - pow(sp->diameter/2, 2);
*/
int	intersect_sphere(t_xyz pos, t_xyz pix_dir, t_sphere *sp, t_xyz *intersect_pt)
{
	t_xyz	oc;
	double	t;
	double	discr;
	
	oc = subtractV(pos, *sp->position);
	discr = (2 * multiplyVs(oc, pix_dir) * 2 * multiplyVs(oc, pix_dir)) 
			- 4 * multiplyVs(pix_dir, pix_dir) * (multiplyVs(oc, oc) 
			- pow(sp->diameter/2, 2));
	if (discr < 0)
		return (0);
	t = (-(2 * multiplyVs(oc, pix_dir)) - sqrt(discr)) / 
		(2 * multiplyVs(pix_dir, pix_dir));
	*intersect_pt = addV(pos, multiplyV(pix_dir, t));
	return (1);	
}

int intersect_plane(t_xyz pos, t_xyz pix_dir, t_plane *pl, t_xyz *intersect_pt)
{
	double	dotND;
	double	t;
	t_xyz	vecOP;

	dotND = multiplyVs(*pl->norm_vect, pix_dir);
	if (fabs(dotND) < 1e-6)
		return (0);
	vecOP = subtractV(*pl->position, pos);
	t = multiplyVs(vecOP, *pl->norm_vect) / dotND;
	if (t < 0)
		return (0);
	*intersect_pt = addV(pos, multiplyV(pix_dir, t));
	return (1);
}














double distance(t_xyz p1, t_xyz p2) {
	return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));
}

int	solve_plane(t_xyz pos, t_xyz pix_dir, t_plane pl, t_xyz *intersect_pt)
{
	double denom;
	double t;
	t_xyz vecOP;
	
	denom = multiplyVs(*pl.norm_vect, pix_dir);
	if (fabs(denom) < 1e-6)
		return (0);
	vecOP = subtractV(*pl.position, pos);
	t = multiplyVs(vecOP, *pl.norm_vect) / denom;
	if (t < 0)
		return (0);
	*intersect_pt = addV(pos, multiplyV(pix_dir, t));
	return (1);
}

int	within_cylinder_radius(t_xyz *intersect_pt, t_cylinder *cy, t_xyz *cap_center)
{
    double	dist;
	
	dist = distance(*intersect_pt, *cap_center);
	if (dist <= (cy->diameter / 2.0))
		return (1);
	return (0);
}

int solve_cylinder(t_xyz pos, t_xyz pix_dir, t_cylinder *cy, t_xyz *intersect_pt)
{
    t_xyz CO = subtractV(pos, *cy->position);
    t_xyz V = normalizeV(*cy->norm_vect);
    double r = cy->diameter/2;
    t_xyz D_perp = subtractV(pix_dir, multiplyV(V, multiplyVs(pix_dir, V)));
    t_xyz CO_perp = subtractV(CO, multiplyV(V, multiplyVs(CO, V)));

    double A = multiplyVs(D_perp, D_perp);
    double B = 2 * multiplyVs(D_perp, CO_perp);
    double C = multiplyVs(CO_perp, CO_perp) - pow(r, 2);

    double discriminant = pow(B, 2) - 4 * A * C;
    if (discriminant < 0)
        return 0;
    double sqrtDiscriminant = sqrt(discriminant);
    double t0 = (-B - sqrtDiscriminant) / (2 * A);
    double t1 = (-B + sqrtDiscriminant) / (2 * A);

    if (t0 > t1) { double temp = t0; t0 = t1; t1 = temp; }

    double t = (t0 >= 0) ? t0 : ((t1 >= 0) ? t1 : -1);
    if (t < 0)
        return 0;	
    *intersect_pt = addV(pos, multiplyV(pix_dir, t));
    return 1;
}

/*int within_cylinder_tube(t_cylinder *cy, t_xyz *intersect_pt)
{
    // Normalize the direction vector
    t_xyz norm_dir = normalizeV(*(cy->norm_vect));

    // Calculate the vector from the cylinder's center to the intersection point
    t_xyz center_to_point = subtractV(*intersect_pt, *(cy->position));

    // Project this vector onto the cylinder's normalized direction
    double proj_length = multiplyVs(center_to_point, norm_dir);

    // Check if the projected length is within the half-height bounds of the cylinder
    // Assuming the 'position' is the center of the cylinder
    double half_height = cy->height / 2.0;
    return (fabs(proj_length) <= half_height) ? 1 : 0;
}*/

int within_cylinder_tube(t_cylinder *cy, t_xyz *intersect_pt)
{
    t_xyz norm_dir = normalizeV(*(cy->norm_vect));

    // Calculate the vector from the cylinder's center to the intersection point
    t_xyz center_to_point = subtractV(*intersect_pt, *(cy->position));

    // Project this vector onto the cylinder's normalized direction
    double proj_length = multiplyVs(center_to_point, norm_dir);

    // Calculate deformation factors directly affecting the projected length
    double deformation_factor = fabs((double)norm_dir.x) + fabs((double)norm_dir.y) + fabs((double)norm_dir.z);
    if (deformation_factor < 1e-6) {
        deformation_factor = 1;  // To handle cases where direction vector is almost zero
    }

    // Adjust the half-height by considering the deformation factor
    double adjusted_half_height = (cy->height / 2.0) * deformation_factor;

    // Check if the projected length is within the adjusted bounds of the cylinder
    return (fabs(proj_length) <= adjusted_half_height) ? 1 : 0;
}


int	intersect_cylinder(t_xyz pos, t_xyz pix_dir, t_cylinder *cy, t_xyz *intersect_pt)
{
	t_plane pl1;
	t_plane	pl2;
	int		ret;
	
	ret = 0;
	pl1.norm_vect = ft_safe_malloc(sizeof(t_xyz), data_destroy, NULL);
	pl1.position = ft_safe_malloc(sizeof(t_xyz), data_destroy, NULL);
	pl2.norm_vect = ft_safe_malloc(sizeof(t_xyz), data_destroy, NULL);
	pl2.position = ft_safe_malloc(sizeof(t_xyz), data_destroy, NULL);
	*pl1.norm_vect = *cy->norm_vect;
	*pl1.position = addV(*cy->position, multiplyV(*cy->norm_vect, cy->height / 2.0));
	*pl2.norm_vect = multiplyV(*cy->norm_vect, -1);
	*pl2.position = subtractV(*cy->position, multiplyV(*cy->norm_vect, cy->height / 2.0));
	if (solve_plane(pos, pix_dir, pl1, intersect_pt) && within_cylinder_radius(intersect_pt, cy, pl1.position))
		ret = 1;
	if (solve_plane(pos, pix_dir, pl2, intersect_pt) && within_cylinder_radius(intersect_pt, cy, pl2.position))
		ret = 1;
	if (solve_cylinder(pos, pix_dir, cy, intersect_pt) && within_cylinder_tube(cy, intersect_pt))
		ret = 1;
	free(pl1.norm_vect);
	free(pl1.position);
	free(pl2.norm_vect);
	free(pl2.position);
	return (ret);
}

void	object_intersections(t_data *dt, t_xyz pixel_dir, int pixel)
{
	t_rgb	color;
	t_xyz	*intersect_pt;	// MALLOC
	
	intersect_pt = ft_safe_malloc(sizeof(t_xyz), data_destroy, NULL);
	if (intersect_cylinder(*dt->camera->position, pixel_dir, dt->cylinder, intersect_pt))
	{
		color = base_color(dt, *dt->cylinder->color); // dt->obj->color
		color = lit_color_cy(dt, color, intersect_pt, dt->cylinder); // dt->obj->pos
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
	free(intersect_pt);
	// Intersect CYLINDERS
	// Intersect PLANES
}

/*
void	paint_pixel(int value, t_xyz intersect_pt, t_rgb obj_color)
{
	t_rgb	color;
	
	if (value)
	{
		color = base_color(dt, obj_color);
		color = lit_color_sp(dt, color, intersect_pt, dt->sphere);
		dt->img.img_data[pixel + 0] = color.b;
		dt->img.img_data[pixel + 1] = color.g;
		dt->img.img_data[pixel + 2] = color.r;
	}
	else
	{
		dt->img.img_data[pixel + 0] = 255;
		dt->img.img_data[pixel + 1] = 255;
		dt->img.img_data[pixel + 2] = 255;
	}
}*/


/*

User
Forget the snippets you provided me lets start fresh, I have the height, diameter, position and normal vector of a cylinder (everything I need to calculate the shape) in order to solve the cylinder I have to separate it in different parts, the two caps and the cylindrical shape, I am going to calculate the intersection point for the ray in each one of them if it returns 1 there is intersection but the *intersection_pt will only be updated if the distance is smaller that the last intersection point (you can make a separate fucntion to chek so) here is the structure I want you to follow to provide me the correct code to achive this:

int	solve_plane(t_xyz pos, t_xyz pix_dir, t_plane pl, t_xyz *intersect_pt)
{
	
}

int	solve_cylinder(t_xyz pos, t_xyz pix_dir, t_cylinder *cy, t_xyz *intersection_pt)
{
	
}

int	intersect_cylinder(t_xyz pos, t_xyz pix_dir, t_cylinder *cy, t_xyz *intersect_pt)
{
	t_plane pl1;
	t_plane	pl2;
	int		ret;
	
	ret = 0;
	pl1.norm_vect = 
	pl1.position = 
	pl2.norm_vect =
	pl2.position =
	if (solve_plane(pos, pix_dir, pl1, intersect_pt))
		ret = 1;
	if (solve_plane(pos, pix_dir, pl2, intersect_pt))
		ret = 1;
	if (solve_cylinder(pos, pix_dir, cy, intersect_pt))
		ret = 1;
	return (ret);
} 

*/