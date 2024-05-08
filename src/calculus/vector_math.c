/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:49:29 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/08 01:28:24 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

t_xyz	norm_v(t_xyz v)
{
	double	lenght;

	lenght = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v.x /= lenght;
	v.y /= lenght;
	v.z /= lenght;
	return (v);
}

t_xyz	add_v(t_xyz v1, t_xyz v2)
{
	t_xyz	ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	return (ret);
}

t_xyz	subtr_v(t_xyz v1, t_xyz v2)
{
	t_xyz	ret;

	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	return (ret);
}

t_xyz	mult_v(t_xyz v, double scalar)
{
	t_xyz	ret;

	ret.x = v.x * scalar;
	ret.y = v.y * scalar;
	ret.z = v.z * scalar;
	return (ret);
}

double	dot(t_xyz v1, t_xyz v2)
{
	t_xyz	ret;
	double	ret_val;

	ret.x = v1.x * v2.x;
	ret.y = v1.y * v2.y;
	ret.z = v1.z * v2.z;
	ret_val = ret.x + ret.y + ret.z;
	return (ret_val);
}

t_xyz cross_v(t_xyz v1, t_xyz v2)
{
    t_xyz result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}