/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:10:55 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/07 14:15:37 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

/*
hello, I been doing some tests and I nodest a big error, when I set the camera normal axis to -1 in the X or Y axis the camera turns to the 
*/

void	blackout_screen(t_data *dt)
{
	// TODO: Delete previus Image
	for (int i = 0; i < W_HEIGHT * W_WIDTH * 4; i++)
        dt->img.img_data[i] = 0;
    mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img.img_ptr, 0, 0);
}

void	update_parameters(t_data *dt)
{
	blackout_screen(dt);
	draw_viewport(dt);
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img.img_ptr, 0, 0);
}

int	key_press(int keycode)
{
	t_data	*dt;

	dt = data();
	printf("Key: %d\n", keycode);
	if (keycode == K_ESC)
	{
		data_destroy();
		printf("%sESC button clicked%s\n", RED, WHITE);
		exit(0);
	}
	if (keycode == K_LEFT)
		dt->camera->position.x -= 5; 
	if (keycode == K_RIGHT)
		dt->camera->position.x += 5; 
	if (keycode == K_UP)
		dt->camera->position.y -= 5;
	if (keycode == K_DOWN)
		dt->camera->position.y += 5;
	update_parameters(dt);
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
