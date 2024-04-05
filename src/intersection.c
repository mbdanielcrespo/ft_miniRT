/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 21:03:07 by danalmei          #+#    #+#             */
/*   Updated: 2024/04/05 21:11:29 by danalmei         ###   ########.fr       */
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
	t_xyz	intersect_pt;
	double	t;
	double	a;
	double	b;
	double	c;
	double	discr;
	
	oc = subtractV(pos, *sp->position);
	/*printf("Sphere pos: \n");
	print_trpl_float(sp->position);
	printf("Camera pos: \n");
	print_trpl_float(&pos);
	printf("OC vector: \n");
	print_trpl_float(&oc);
	printf("Pix dir: \n");
	print_trpl_float(&pix_dir);
	printf("\n");*/
	a = multiplyVs(pix_dir, pix_dir);
	b = 2 * multiplyVs(oc, pix_dir);
	c = multiplyVs(oc, oc) - pow(sp->diameter/2, 2);
	discr = b*b - 4*a*c;
	if (discr < 0)
		return (0);
	/*if (t < 0) {
        t = (-b + sqrt(discr)) / (2*a);
        if (t < 0) return 0; // Both intersections are behind the camera
    }*/
	t = (-b - sqrt(discr)) / (2*a);
	intersect_pt = addV(pos, multiplyV(pix_dir, t));
	//print_trpl_float(&intersect_pt);
	//printf("\n");
	return (1);	
}
