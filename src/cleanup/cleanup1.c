/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:33:16 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/20 17:22:30 by feden-pe         ###   ########.fr       */
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
		cylinder = cylinder->next;
		free(tmp);
	}
}

void	destroy_mlx(void)
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
		if (ptr->ambient)
			free(ptr->ambient);
		if (ptr->camera)
			free(ptr->camera);
		if (ptr->light)
			free(ptr->light);
		free_spheres(ptr->sphere);
		free_planes(ptr->plane);
		free_cylinders(ptr->cylinder);
		if (ptr->current_line)
			free(ptr->current_line);
		close(ptr->fd);
	}
	printf("Data destroyed!\n");
}
