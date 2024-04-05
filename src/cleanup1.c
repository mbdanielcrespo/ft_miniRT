/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:33:16 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/29 20:53:22 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

void	free_ambient(t_ambient *ambient)
{
	if (ambient)
	{
		if (ambient->color)
			free(ambient->color);
		free(ambient);
	}
}

void	free_camera(t_camera *camera)
{
	if (camera)
	{
		if (camera->position)
			free(camera->position);
		if (camera->norm_vect)
			free(camera->norm_vect);
		free(camera);
	}
}

void	free_light(t_light *light)
{
	if (light)
	{
		if (light->position)
			free(light->position);
		if (light->color)
			free(light->color);
		free(light);
	}
}

void destroy_mlx(void)
{
	t_data	*ptr;

	ptr = data();
	if (ptr->img.img_ptr)
		mlx_destroy_image(ptr->mlx_ptr, ptr->img.img_ptr);
	if (ptr->win_ptr)
		mlx_destroy_window(ptr->mlx_ptr, ptr->win_ptr);
	if (ptr->mlx_ptr)
		mlx_destroy_display(ptr->mlx_ptr);
	free(ptr->mlx_ptr);
}

void	data_destroy(void)
{
	t_data	*ptr;

	ptr = data();
	destroy_mlx();
	if (ptr)
	{
		free_ambient(ptr->ambient);
		free_camera(ptr->camera);
		free_light(ptr->light);
		free_spheres(ptr->sphere);
		free_planes(ptr->plane);
		free_cylinders(ptr->cylinder);
		if (ptr->current_line)
			free(ptr->current_line);
	}
	printf("Data destroyed!\n");
}
