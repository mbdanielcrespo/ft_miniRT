/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:10:55 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/28 13:06:14 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

int key_press(int keycode)
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

int close_win(void)
{
	data_destroy();
	printf("%sX icon clicked\n%s", RED, WHITE);
    exit(0);
	return (42);
}

void	mlx_setup(void)
{
	t_data			*dt;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	unsigned char	*img_data = NULL;

	dt = data();
	dt->mlx_ptr = mlx_init();
	dt->win_ptr = mlx_new_window(dt->mlx_ptr, W_HEIGHT, W_WIDTH, "miniRT");
	dt->img_ptr = mlx_new_image(dt->mlx_ptr, W_HEIGHT, W_WIDTH);
	img_data = (unsigned char *)mlx_get_data_addr(dt->img_ptr, &bits_per_pixel, &size_line, &endian);
	for (int x = 0, y = 0; y < 900; x++, y++)	// TODO: PROTECTION AGAINST TRYING TO WRITE TO BORDERS
	{
    	int pixel = (x * 4) + (y * size_line); // Assuming 4 bytes per pixel
    	img_data[pixel + 0] = 0xFF; // Blue
    	img_data[pixel + 1] = 0xFF; // Green
    	img_data[pixel + 2] = 0xFF; // Red
    	img_data[pixel + 3] = 0x00; // Alpha (not used)
	}
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img_ptr, 0, 0);
	mlx_key_hook(dt->win_ptr, key_press, NULL);
	mlx_hook(dt->win_ptr, 17, 1L<<17, close_win, NULL);
}

