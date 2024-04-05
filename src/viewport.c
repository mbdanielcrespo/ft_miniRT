/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:30:39 by danalmei          #+#    #+#             */
/*   Updated: 2024/04/05 21:21:51 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

double	deg_to_rad(double deg)
{
	return (deg * (PI / 180));
}

t_xyz	normalizeV(t_xyz v)
{
	double	lenght;

	lenght = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v.x /= lenght;
	v.y /= lenght;
	v.z /= lenght;
	return (v);
}

t_xyz	addV(t_xyz v1, t_xyz v2)
{
	t_xyz	ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	return (ret);
}

t_xyz	subtractV(t_xyz v1, t_xyz v2)
{
	t_xyz	ret;

	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	return (ret);
}

t_xyz	multiplyV(t_xyz v, double scalar)
{
	t_xyz	ret;

	ret.x = v.x * scalar;
	ret.y = v.y * scalar;
	ret.z = v.z * scalar;
	return (ret);
}

double	multiplyVs(t_xyz v1, t_xyz v2)
{
	t_xyz	ret;
	double	ret_val;

	ret.x = v1.x * v2.x;
	ret.y = v1.y * v2.y;
	ret.z = v1.z * v2.z;
	ret_val = ret.x + ret.y + ret.z;
	return (ret_val);
}

t_viewport	set_viewport(t_viewport vp)
{
	t_data	*ptr;

	ptr = data();
	
	triple_float(&vp.camUp, "0,1,0");
	triple_float(&vp.camRight, "1,0,0");
	return (vp);
}

t_xyz	calc_pixel_dir(t_viewport vp, int x, int y)
{
	t_xyz	pixel_dir;
	t_data	*ptr;
	double scale;
	//double	fov_adjustment = tan(vp.fov * 0.5 * (M_PI / 180.0));

	ptr = data();
	vp.view_ratio = (double)W_WIDTH / (double)W_HEIGHT;
	vp.ndcX = (x + 0.5) / W_WIDTH * 2 - 1;
	vp.ndcY = 1 - (y + 0.5) / W_HEIGHT * 2;
	scale = tan(ptr->camera->field_of_view * 0.5 * (M_PI / 180.0));
	vp.ndcX *= vp.view_ratio * scale;
	vp.ndcY *= scale;
	pixel_dir = addV(addV(multiplyV(vp.camRight, vp.ndcX), 
						  multiplyV(vp.camUp, vp.ndcY)), 
						  multiplyV(*ptr->camera->norm_vect, 1));
	pixel_dir = normalizeV(pixel_dir);
	printf("\nPixel dir:\n");
	print_trpl_float(&pixel_dir);
	return (pixel_dir);
}

void	draw_viewport(t_data *dt)
{
	int			x;
	int			y;
	int			pixel;
	t_viewport 	vp = {0};
	t_xyz		pixel_dir;

	vp = set_viewport(vp);
	y = -1;
	printf("Image status:\n");
	while (++y < W_HEIGHT)
	{
		x = -1;
		while (++x < W_WIDTH)
		{
			pixel_dir = calc_pixel_dir(vp, x, y);
			(void)pixel_dir;
			pixel = (x * dt->img.bpp / 8) + (y * dt->img.line_size);
			//printf("%.0f\r", ((double)pixel / 4) / (W_HEIGHT * W_WIDTH) * 100);			//Print image generation status
			if (intersect_sphere(*dt->camera->position, pixel_dir, dt->sphere))
			{
				dt->img.img_data[pixel + 0] = 255;
				dt->img.img_data[pixel + 1] = 0;
				dt->img.img_data[pixel + 2] = 0;
			}
			else
			{
				dt->img.img_data[pixel + 0] = 255;
				dt->img.img_data[pixel + 1] = 255;
				dt->img.img_data[pixel + 2] = 255;
			}
		}
	}
	printf("\n");
	//setPixelColor(x, y, 0xFFFFFF);
}


/*

I don't think the calculation of the pixel direction is being doing right, here is why, In the same case as before:

Sphere pos 0,0,200 size 10
Camera pos 0,0,0 normal vector 0,0,1

the calculated pixel vector is always 0,0,1 meaning its going to render the vector in the same direction always, what I think is the right aproach to this case is to shoot a ray (pixel_vector)

*/