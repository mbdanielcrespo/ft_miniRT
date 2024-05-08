/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:30:39 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/08 15:49:31 by danalmei         ###   ########.fr       */
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
		vp.cam_forward = ptr->camera->norm_vect;
		vp.cam_right = norm_v(cross_v((t_xyz){0, 1, 0}, vp.cam_forward));
		vp.cam_up = cross_v(vp.cam_forward, vp.cam_right);
	}
	vp.ndc_x = (x + 0.5) / W_WIDTH * 2 - 1;
	vp.ndc_y = 1 - (y + 0.5) / W_HEIGHT * 2;
	vp.view_ratio = (double)W_WIDTH / (double)W_HEIGHT;
	vp.ndc_x *= vp.view_ratio * vp.scale;
	vp.scale = tan(ptr->camera->field_of_view * 0.5 * (PI / 180.0));
	vp.ndc_y *= vp.scale;
	return (vp);
}

t_xyz	calc_pixel_dir(t_viewport vp)
{
	t_xyz	pix_dir;

	pix_dir = norm_v(add_v(add_v(mult_v(vp.cam_right, vp.ndc_x),
				mult_v(vp.cam_up, vp.ndc_y)), vp.cam_forward));
	return (pix_dir);
}

void	draw_viewport(t_data *dt)
{
	int			x;
	int			y;
	int			pixel;
	t_viewport	vp = {0};
	t_xyz		pixel_dir;
	int			intersec;

	intersec = 0;
	y = -1;
	printf("Image status:\n");
	while (++y < W_HEIGHT)
	{
		x = -1;
		while (++x < W_WIDTH)
		{
			vp = set_viewport(vp, x, y);
			dt->vp = vp;
			pixel_dir = calc_pixel_dir(vp);
			pixel = (x * dt->img.bpp / 8) + (y * dt->img.line_size);
			printf("%.0f\r", ((double)pixel / 4) / (W_HEIGHT * W_WIDTH) * 100);
			object_intersections(dt, pixel_dir, pixel, intersec);
		}
	}
	printf("\n");
}
