/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:30:39 by danalmei          #+#    #+#             */
/*   Updated: 2024/04/08 00:54:44 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

t_viewport	set_viewport(t_viewport vp, int x, int y)
{
	t_data	*ptr;

	ptr = data();
	(void)ptr;
	if (x == 0 && y == 0)
	{
		vp.scale = tan(ptr->camera->field_of_view * 0.5 * (PI / 180.0));
		triple_float(&vp.camUp, "0,1,0");
		triple_float(&vp.camRight, "1,0,0");
	}
	vp.ndcX = (x + 0.5) / W_WIDTH * 2 - 1;
	vp.ndcY = 1 - (y + 0.5) / W_HEIGHT * 2;
	vp.view_ratio = (double)W_WIDTH / (double)W_HEIGHT;
	vp.ndcX *= vp.view_ratio * vp.scale;
	vp.ndcY *= vp.scale;
	return (vp);
}

t_xyz	calc_pixel_dir(t_viewport vp)
{
	t_xyz	pixel_dir;
	t_xyz	pix_x;
	t_xyz	pix_y;
	t_xyz	pix_z;
	t_data	*ptr;

	ptr = data();
	pix_x = multiplyV(vp.camRight, vp.ndcX);
	pix_y = multiplyV(vp.camUp, vp.ndcY);
	pix_z = multiplyV(*ptr->camera->norm_vect, 1);
	pixel_dir = addV(addV(pix_x, pix_y), pix_z);
	return (pixel_dir);
}

t_rgb	base_color(t_data *dt, t_rgb starting_col)
{
	t_ambient	A;
	t_rgb		base_color;
	
	
	// TODO: ERROR IF AMBIENT IS >1
	A = *dt->ambient;
	base_color.r  = (starting_col.r * A.intensity * A.color->r) / 255;
	base_color.g  = (starting_col.g * A.intensity * A.color->g) / 255;
	base_color.b  = (starting_col.b * A.intensity * A.color->b) / 255;
	// Take in consideration color value for ambient light ***
	//printf("Calculated base color:\n");
	//print_trpl_int(base_color);
	return (base_color);
}

/*
t_rgb	lit_color(t_data *dt, t_rgb base_col)
{
	t_light	L;
	t_rgb	lit_color;

	L = dt->light;
	
}*/


void	draw_on_screen(t_data *dt, t_xyz pixel_dir, int pixel)
{
	// Calculate AMBIENT LIGHT (base color) = intensity * initial color 
	// Calculate DIFUSE LIGHT (directional light from points)
	// Calculate SPECULAR LIGHT (bright spots) = bright spots
	object_intersections(dt, pixel_dir, pixel);
}


void	draw_viewport(t_data *dt)
{
	int			x;
	int			y;
	int			pixel;
	t_viewport 	vp = {0};
	t_xyz		pixel_dir;

	y = -1;
	printf("Image status:\n");
	while (++y < W_HEIGHT)
	{
		x = -1;
		while (++x < W_WIDTH)
		{
			vp = set_viewport(vp, x, y);
			pixel_dir = calc_pixel_dir(vp);
			pixel = (x * dt->img.bpp / 8) + (y * dt->img.line_size);
			printf("%.0f\r", ((double)pixel / 4) / (W_HEIGHT * W_WIDTH) * 100);			//Print image generation status
			draw_on_screen(dt, pixel_dir, pixel);
		}
	}
	printf("\n");
}


/*

I don't think the calculation of the pixel direction is being doing right, here is why, In the same case as before:

Sphere pos 0,0,200 size 10
Camera pos 0,0,0 normal vector 0,0,1

the calculated pixel vector is always 0,0,1 meaning its going to render the vector in the same direction always, what I think is the right aproach to this case is to shoot a ray (pixel_vector)

*/