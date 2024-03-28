/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:10:55 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/28 17:06:56 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

int	key_press(int keycode)
{
	printf("Key: %d\n", keycode);
	if (keycode == K_ESC)
	{
		data_destroy();
		printf("%sESC button clicked%s\n", RED, WHITE);
		exit(0); // Exit the program
	}
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
	dt->img_ptr = mlx_new_image(dt->mlx_ptr, W_HEIGHT, W_WIDTH);
	draw_viewport(dt);
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img_ptr, 0, 0);
	mlx_key_hook(dt->win_ptr, key_press, NULL);
	mlx_hook(dt->win_ptr, 17, 1L<<17, close_win, NULL);
}

