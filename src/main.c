/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:29:39 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/28 12:17:49 by danalmei         ###   ########.fr       */
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

	A	0.2 			255,255,255							(Ambient lighting	Ratio				RGB Colors)
	C	-50.0,0,20 		0,0,1 		70 						(Camera				XYZ of viewpoint	3d normalized vector	FOV)
	L 	-40.0,50.0,0.0 	0.6 		10,0,255				(Light				XYZ coordinates 	Light brightness		RGB Colors)

	sp	0.0,0.0,20.6	12.6 		10,0,255				(Sphere				XYZ coordnates		sphere diameter			RGB Colors)
	pl	0.0,0.0,-10.0 	0.0,1.0,0.0	0,0,225					(Plane				XYZ coordinates		3d normalized vector	RGB Colors)
	cy	50.0,0.0,20.6 	0.0,0.0,1.0 14.2	21.42 10,0,255 	(Cylinder	XYZ coordinates		3d normalized vector	diameter	height	RGB Colors)
*/

#include <main.h>

int main(int ac, char **av)
{
	t_data	*data_ptr;

	data_ptr = data();
	if (ac == 2)
	{
		init_data(av);
		print_data();
		mlx_setup();
		//	simulation
		mlx_loop(data_ptr->mlx_ptr);
		data_destroy();
	}
	else
		ft_error("Invalid number of arguments!");
	return (0);
}
/*

mlx_ptr = mlx_init();
    width = 800;
    height = 600;
    win_ptr = mlx_new_window(mlx_ptr, width, height, "MiniLibX Window");

    // Create a new image.
    img_ptr = mlx_new_image(mlx_ptr, width, height);
    img_data = mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);

    // Define a color (in this case, white).
    color = 0xFFFFFF;

    // Draw a simple line on the image.
    // Note: You'd usually use a function to draw more complex shapes.
    int x = 100;
    for (int y = 100; y < 200; y++)
    {
        *(int*)(img_data + (x + y * width) * (bits_per_pixel / 8)) = color;
        x++; // Simple way to make the line diagonal.
    }

    // Put the image on the window.
    mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);

    // Enter the MLX loop to display the window.
    mlx_loop(mlx_ptr);

    return (0);

*/