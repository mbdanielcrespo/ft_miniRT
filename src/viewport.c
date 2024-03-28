/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:30:39 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/28 17:16:47 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

double	deg_to_rad(double deg)
{
	return (deg * (PI / 180));
}

t_xyz	normalize(t_xyz v)
{
	double	lenght;

	lenght = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v.x /= lenght;
	v.y /= lenght;
	v.z /= lenght;
	return (v);
}

t_xyz	add(t_xyz v1, t_xyz v2)
{
	t_xyz	ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	return (ret);
}

t_xyz	multiply(t_xyz v, double scalar)
{
	t_xyz	ret;

	ret.x = v.x * scalar;
	ret.y = v.y * scalar;
	ret.z = v.z * scalar;
	return (ret);
}

t_viewport	set_viewport(t_viewport vp)
{
	t_data	*ptr;

	ptr = data();
	vp.view_ratio = (double)W_HEIGHT / (double)W_WIDTH;
	vp.viewport_H = 2 * tan(deg_to_rad(ptr->camera->field_of_view) / 2);
	vp.viewport_W = vp.viewport_H * vp.view_ratio;
	triple_float(&vp.camUp, "0,1,0");
	triple_float(&vp.camRight, "1,0,0");
	return (vp);
}

t_xyz	calc_pixel_dir(t_viewport vp, int x, int y)
{
	t_xyz	pixel_dir;
	t_data	*ptr;

	ptr = data();
	vp.ndcX = ((x + 0.5) / (W_WIDTH * 2)) - 1;
	vp.ndcY = 1 - ((y + 0.5) / (W_HEIGHT * 2));
	pixel_dir.x = vp.ndcX * vp.viewport_W;
	pixel_dir.y = vp.ndcY * vp.viewport_H;
	pixel_dir.z = 1;
	pixel_dir = add(add(multiply(vp.camRight, pixel_dir.x), 
					multiply(vp.camUp, pixel_dir.y)), 
					multiply(*ptr->camera->norm_vect, pixel_dir.z));
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
	while (++y < W_HEIGHT)
	{
		x = -1;
		while (++x < W_WIDTH)
		{
			pixel_dir = calc_pixel_dir(vp, x, y);
			pixel = (x * BPP / 8) + (y * LINE_SIZE);
        	dt->img_data[pixel + 0] = 255;				// INIT IMG DATA TO NULL
        	dt->img_data[pixel + 1] = 255;
        	dt->img_data[pixel + 2] = 255;
       	 	//if (BPP == 32) {
            //	img_data[pixel + 3] = 0; // Alpha channel, if used
        }
	}
	//setPixelColor(x, y, 0xFFFFFF);
}
