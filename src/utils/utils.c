/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:50:19 by danalmei          #+#    #+#             */
/*   Updated: 2024/04/28 22:22:44 by danalmei         ###   ########.fr       */
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
