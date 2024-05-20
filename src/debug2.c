/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:30:21 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/20 14:46:46 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

void	print_trpl_float(t_xyz trpl_float)
{
	printf("    %sx: %.2Lf%s\n", L_GREEN, trpl_float.x, WHITE);
	printf("    %sy: %.2Lf%s\n", L_GREEN, trpl_float.y, WHITE);
	printf("    %sz: %.2Lf%s\n", L_GREEN, trpl_float.z, WHITE);
}

void	print_trpl_int(t_rgb trpl_int)
{
	printf("    %sr: %d%s\n", L_GREEN, trpl_int.r, WHITE);
	printf("    %sb: %d%s\n", L_GREEN, trpl_int.b, WHITE);
	printf("    %sg: %d%s\n", L_GREEN, trpl_int.g, WHITE);
}

void	print_spheres(t_sphere *sphere)
{
	t_sphere	*tmp;
	int			c;

	c = 1;
	tmp = sphere;
	while (tmp)
	{
		printf("	%sSphere N%d:%s\n", L_YELLOW, c, WHITE);
		printf("	%sdiameter:%s %.1Lf%s\n", L_BLUE, L_GREEN,
			tmp->diameter, WHITE);
		printf("	%s[position]%s\n", L_BLUE, WHITE);
		print_trpl_float(tmp->position);
		printf("	%s[color]%s\n", L_BLUE, WHITE);
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
		printf("    %sdiameter:%s %.1Lf%s\n", L_BLUE, L_GREEN,
			tmp->diameter, WHITE);
		printf("    %sheight:%s %.1Lf%s\n", L_BLUE, L_GREEN,
			tmp->height, WHITE);
		printf("    %s[position]%s\n", L_BLUE, WHITE);
		print_trpl_float(tmp->position);
		printf("    %s[normal vecotr]%s\n", L_BLUE, WHITE);
		print_trpl_float(tmp->norm_vect);
		printf("    %s[color]%s\n", L_BLUE, WHITE);
		print_trpl_int(tmp->color);
		tmp = tmp->next;
	}
}
