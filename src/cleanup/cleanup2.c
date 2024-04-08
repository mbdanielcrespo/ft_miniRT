/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:33:16 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/28 10:27:31 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

void	free_spheres(t_sphere *sphere)
{
	t_sphere	*tmp;
	
	tmp = sphere;
	while (sphere)
	{
		tmp = sphere;
		if (sphere->position)
			free(sphere->position);
		if (sphere->color)
			free(sphere->color);
		sphere = sphere->next;
		free(tmp);
	}
}

void	free_planes(t_plane *plane)
{
	t_plane	*tmp;
	
	tmp = plane;
	while (plane)
	{
		tmp = plane;
		if (plane->position)
			free(plane->position);
		if (plane->norm_vect)
			free(plane->norm_vect);
		if (plane->color)
			free(plane->color);
		plane = plane->next;
		free(tmp);
	}
}

void	free_cylinders(t_cylinder *cylinder)
{
	t_cylinder	*tmp;
	
	tmp = cylinder;
	while (cylinder)
	{
		tmp = cylinder;
		if (cylinder->position)
			free(cylinder->position);
		if (cylinder->norm_vect)
			free(cylinder->norm_vect);
		if (cylinder->color)
			free(cylinder->color);
		cylinder = cylinder->next;
		free(tmp);
	}
}
