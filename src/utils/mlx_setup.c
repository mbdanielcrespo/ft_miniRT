/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:10:55 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/20 14:59:00 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

void	update_parameters(t_data *dt)
{
	// TODO: Delete previus Image?
	int	i;

	i = 0;
	while (i < W_HEIGHT * W_WIDTH * 4)
		dt->img.img_data[i++] = 0;
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img.img_ptr, 0, 0);
	draw_viewport(dt);
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img.img_ptr, 0, 0);
}

int	key_press(int keycode)
{
	t_data	*dt;

	dt = data();
	if (keycode == K_ESC)
	{
		data_destroy();
		printf("%sESC button clicked%s\n", RED, WHITE);
		exit(0);
	}
	camera_settings(dt, keycode);
	return (0);
}

int	close_win(void)
{
	data_destroy();
	printf("%sX icon clicked\n%s", RED, WHITE);
	exit(0);
	return (42);
}

void	mlx_setup(void)
{
	t_data			*dt;

	dt = data();
	dt->mlx_ptr = mlx_init();
	dt->win_ptr = mlx_new_window(dt->mlx_ptr, W_HEIGHT, W_WIDTH, "miniRT");
	dt->img.img_ptr = mlx_new_image(dt->mlx_ptr, W_HEIGHT, W_WIDTH);
	dt->img.img_data = (unsigned char *)mlx_get_data_addr(dt->img.img_ptr,
			&dt->img.bpp, &dt->img.line_size, &dt->img.endian);
	draw_viewport(dt);
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img.img_ptr, 0, 0);
	mlx_key_hook(dt->win_ptr, key_press, NULL);
	mlx_hook(dt->win_ptr, 17, 1L << 17, close_win, NULL);
}
