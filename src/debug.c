/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:55:52 by danalmei          #+#    #+#             */
/*   Updated: 2024/04/07 19:35:49 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

void	print_data(void)
{
	printf("Data:\n{\n");
	printf("  %sAmbient:%s\n", L_YELLOW, WHITE);
	if (data()->ambient)
		print_ambient(data()->ambient);
	printf("  %sCamera:%s\n", L_YELLOW, WHITE);
	if (data()->camera)
		print_camera(data()->camera);
	printf("  %sLight:%s\n", L_YELLOW, WHITE);
	if (data()->light)
		print_light(data()->light);
	printf("  %sSpheres:%s\n", L_YELLOW, WHITE);
	if (data()->sphere)
		print_spheres(data()->sphere);
	printf("  %sPlanes:%s\n", L_YELLOW, WHITE);
	if (data()->plane)
		print_planes(data()->plane);
	printf("  %sCylinders:%s\n", L_YELLOW, WHITE);
	if (data()->cylinder)
		print_cylinders(data()->cylinder);
	printf("}\n");
}

void	print_trpl_float(t_xyz *trpl_float)
{
	printf("    %sx: %.2Lf%s\n", L_GREEN, trpl_float->x, WHITE);
	printf("    %sy: %.2Lf%s\n", L_GREEN, trpl_float->y, WHITE);
	printf("    %sz: %.2Lf%s\n", L_GREEN, trpl_float->z, WHITE);
}

void	print_trpl_float_1(t_xyz *trpl_float)
{
	printf("x: %.2Lf\n", trpl_float->x);
	printf("y: %.2Lf\n", trpl_float->y);
	printf("z: %.2Lf\n", trpl_float->z);
}

void	print_trpl_int(t_rgb *trpl_int)
{
	printf("    %sr: %d%s\n", L_GREEN, trpl_int->r, WHITE);
	printf("    %sb: %d%s\n", L_GREEN, trpl_int->b, WHITE);
	printf("    %sg: %d%s\n", L_GREEN, trpl_int->g, WHITE);
}

void	print_ambient(t_ambient *ambient)
{
	printf("    %sintensity:%s %.1Lf%s\n", L_BLUE, L_GREEN, ambient->intensity, WHITE);
	printf("    %s[color]%s\n", L_BLUE, WHITE);
	print_trpl_int(ambient->color);
}

void	print_camera(t_camera *cam)
{
	printf("    %sFOV:%s %.1Lf%s\n", L_BLUE, L_GREEN, cam->field_of_view, WHITE);
	printf("    %s[position]%s\n", L_BLUE, WHITE);
	print_trpl_float(cam->position);
	printf("    %s[normal vecotr]%s\n", L_BLUE, WHITE);
	print_trpl_float(cam->norm_vect);
}
void	print_light(t_light *light)
{
	printf("    %sbrightness:%s %.1Lf%s\n", L_BLUE, L_GREEN, light->brightness, WHITE);
	printf("    %s[position]%s\n", L_BLUE, WHITE);
	print_trpl_float(light->position);
	printf("    %s[color]%s\n", L_BLUE, WHITE);
	print_trpl_int(light->color);
}


void	print_spheres(t_sphere *sphere)
{
	t_sphere	*tmp;
	int			c;

	c = 1;
	tmp = sphere;
	while (tmp)
	{
		printf("  %sSphere N%d:%s\n", L_YELLOW, c, WHITE);
		printf("    %sdiameter:%s %.1Lf%s\n",L_BLUE,  L_GREEN, tmp->diameter, WHITE);
		printf("    %s[position]%s\n", L_BLUE, WHITE);
		print_trpl_float(tmp->position);
		printf("    %s[color]%s\n", L_BLUE, WHITE);
		print_trpl_int(tmp->color);
		tmp = tmp->next;
		c++;
	}
}

void	print_planes(t_plane *plane)
{
	t_plane	*tmp;

	tmp = plane;
	while (tmp)
	{
		printf("    %s[position]%s\n", L_BLUE, WHITE);
		print_trpl_float(tmp->position);
		printf("    %s[normal vecotr]%s\n", L_BLUE, WHITE);
		print_trpl_float(tmp->norm_vect);
		printf("    %s[color]%s\n", L_BLUE, WHITE);
		print_trpl_int(tmp->color);
		tmp = tmp->next;
	}
}
void	print_cylinders(t_cylinder *cylinder)
{
	t_cylinder	*tmp;

	tmp = cylinder;
	while (tmp)
	{
		printf("    %sdiameter:%s %.1Lf%s\n",L_BLUE, L_GREEN, tmp->diameter, WHITE);
		printf("    %sheight:%s %.1Lf%s\n",L_BLUE, L_GREEN, tmp->height, WHITE);
		printf("    %s[position]%s\n", L_BLUE, WHITE);
		print_trpl_float(tmp->position);
		printf("    %s[normal vecotr]%s\n", L_BLUE, WHITE);
		print_trpl_float(tmp->norm_vect);
		printf("    %s[color]%s\n", L_BLUE, WHITE);
		print_trpl_int(tmp->color);
		tmp = tmp->next;
	}
}