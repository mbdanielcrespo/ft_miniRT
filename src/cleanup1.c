/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:33:16 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/28 12:55:36 by danalmei         ###   ########.fr       */
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
	t_data	*data_ptr;

	data_ptr = data();
	if (data_ptr->img_ptr)
		mlx_destroy_image(data_ptr->mlx_ptr, data_ptr->img_ptr);
	if (data_ptr->win_ptr)
		mlx_destroy_window(data_ptr->mlx_ptr, data_ptr->win_ptr);
	if (data_ptr->mlx_ptr)
		mlx_destroy_display(data_ptr->mlx_ptr);
	free(data_ptr->mlx_ptr);
}

void	data_destroy(void)
{
	t_data	*data_ptr;

	data_ptr = data();
	destroy_mlx();
	if (data_ptr)
	{
		free_ambient(data_ptr->ambient);
		free_camera(data_ptr->camera);
		free_light(data_ptr->light);
		free_spheres(data_ptr->sphere);
		free_planes(data_ptr->plane);
		free_cylinders(data_ptr->cylinder);
		if (data_ptr->current_line)
			free(data_ptr->current_line);
	}
	printf("Data destroyed!\n");
}
