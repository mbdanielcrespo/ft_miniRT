/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:55:52 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/20 14:47:17 by danalmei         ###   ########.fr       */
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

void	print_ambient(t_ambient *ambient)
{
	printf("    %sintensity:%s %.1Lf%s\n", L_BLUE, L_GREEN, 
		ambient->intensity, WHITE);
	printf("    %s[color]%s\n", L_BLUE, WHITE);
	print_trpl_int(ambient->color);
}

void	print_camera(t_camera *cam)
{
	printf("    %sFOV:%s %.1Lf%s\n", L_BLUE, L_GREEN,
		cam->field_of_view, WHITE);
	printf("    %s[position]%s\n", L_BLUE, WHITE);
	print_trpl_float(cam->position);
	printf("    %s[normal vecotr]%s\n", L_BLUE, WHITE);
	print_trpl_float(cam->norm_vect);
}

void	print_light(t_light *light)
{
	printf("    %sbrightness:%s %.1Lf%s\n", L_BLUE, L_GREEN,
		light->brightness, WHITE);
	printf("    %s[position]%s\n", L_BLUE, WHITE);
	print_trpl_float(light->position);
	printf("    %s[color]%s\n", L_BLUE, WHITE);
	print_trpl_int(light->color);
}
