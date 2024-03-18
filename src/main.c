/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:29:39 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/17 21:43:51 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	infile .rt (scene description)
	Each type of element can be separated by one or more line break(s)
	Each type of information from an element can be separated by one or more space(s).
	Each type of element can be set in any order in the file.
	Elements which are defined by a capital letter can only be declared once in the scene.

	Each element first’s information is the type identifier (composed by one or two
	character(s)), followed by all specific information for each object in a strict
	order such as:

	A	0.2 			255,255,255			(Ambient lighting	Ratio				RGB Colors)
	C	-50.0,0,20 		0,0,1 			70 	(Camera				XYZ of viewpoint	3d normalized vector	FOV)
	L 	-40.0,50.0,0.0 	0.6 	10,0,255	(Light				XYZ coordinates 	Light brightness		RGB Colors)

	sp	0.0,0.0,20.6 	12.6 	10,0,255	(Sphere				XYZ coordnates		sphere diameter			RGB Colors)
	pl 0.0,0.0,-10.0 	0.0,1.0,0.0 0,0,225	(Plane				XYZ coordinates		3d normalized vector	RGB Colors)
	cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255 (Cylinder	XYZ coordinates		3d normalized vector	diameter	height	RGB Colors)
*/



#include <main.h>

int main()
{
	printf("Hello world!\n");
	char *a = "lol";

	printf("%ld\n", ft_strlen(a));
}
