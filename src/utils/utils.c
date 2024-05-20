/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:50:19 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/20 15:00:06 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

double	deg_to_rad(double deg)
{
	return (deg * (PI / 180));
}

double	distance(t_xyz p1, t_xyz p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + 
			pow(p2.z - p1.z, 2)));
}

int	check_rgb(t_rgb *tmp)
{
	if (tmp->r < 0 || tmp->r > 255)
		return (1);
	if (tmp->g < 0 || tmp->g > 255)
		return (1);
	if (tmp->b < 0 || tmp->b > 255)
		return (1);
	return (0);
}

t_xyz	cross_v(t_xyz v1, t_xyz v2)
{
	t_xyz	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}
