/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:30:39 by danalmei          #+#    #+#             */
/*   Updated: 2024/04/26 12:36:28 by danalmei         ###   ########.fr       */
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
	pix_x = multV(vp.camRight, vp.ndcX);
	pix_y = multV(vp.camUp, vp.ndcY);
	pix_z = ptr->camera->norm_vect;
	pixel_dir = addV(addV(pix_x, pix_y), pix_z);
	return (pixel_dir);
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


void	draw_on_screen(t_data *dt, t_xyz pixel_dir, int pixel)
{
	int	intersec;

	intersec = 0;

	object_intersections(dt, pixel_dir, pixel, intersec);
}