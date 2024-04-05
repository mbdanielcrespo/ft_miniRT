/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 21:03:07 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/31 04:42:06 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

/*
Formula quadratica de interseção da origem O para o centro da esfera C
// Calculo de 
*/
int	intersect_sphere(t_xyz pos, t_xyz pix_dir, t_sphere *sp)
{
    t_xyz	oc;
	double	a;
	double	b;
	double	c;
	
	oc = subtractV(pos, *sp->position);
    a = pix_dir.x * pix_dir.x + pix_dir.y * pix_dir.y + pix_dir.z * pix_dir.z;
    b = 2.0 * (oc.x * pix_dir.x + oc.y * pix_dir.y + oc.z * pix_dir.z);
    c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - (sp->diameter/2) * (sp->diameter/2);
    if ((b*b - 4*a*c) >= 0)
		return (1);
    return (0);
}
