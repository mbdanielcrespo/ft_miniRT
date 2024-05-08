/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:08:55 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/08 15:22:16 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

int	is_valid_keycode(int keycode)
{
	if (keycode == K_1 || keycode == K_2 || keycode == K_3 
		|| keycode == K_4 || keycode == K_UP || keycode == K_DOWN
		|| keycode == K_LEFT || keycode == K_RIGHT || keycode == K_W
		|| keycode == K_A || keycode == K_S || keycode == K_D || keycode == K_Z
		|| keycode == K_F || keycode == K_I || keycode == K_O || keycode == K_P
		|| keycode == K_B)
		return (1);
	return (0);
}

void	set_lighting(t_data *dt, int keycode)
{
	if (keycode == K_I)
	{
		if (dt->diffuse_light)
			dt->diffuse_light = 0;
		else
			dt->diffuse_light = 1;
	}
	else if (keycode == K_O)
	{
		if (dt->specular_light)
			dt->specular_light = 0;
		else
			dt->specular_light = 1;
	}
	else if (keycode == K_P)
	{
		if (dt->hard_shadows)
			dt->hard_shadows = 0;
		else
			dt->hard_shadows = 1;
	} 
}

void	translate_pos(t_data *dt, int keycode)
{
	if (keycode == K_LEFT)
        dt->camera->position = add_v(dt->camera->position, mult_v(dt->vp.cam_right, -STEP));
    else if (keycode == K_RIGHT)
        dt->camera->position = add_v(dt->camera->position, mult_v(dt->vp.cam_right, STEP));
    else if (keycode == K_F)
        dt->camera->position = add_v(dt->camera->position, mult_v(dt->vp.cam_up, STEP));
    else if (keycode == K_B)
        dt->camera->position = add_v(dt->camera->position, mult_v(dt->vp.cam_up, -STEP));
	else if (keycode == K_UP)
		dt->camera->position = add_v(dt->camera->position, mult_v(dt->vp.cam_forward, STEP));
	else if (keycode == K_DOWN)
		dt->camera->position = add_v(dt->camera->position, mult_v(dt->vp.cam_forward, -STEP));
}

void	camera_settings(t_data *dt, int keycode)
{
	if (keycode == K_F || keycode == K_B || keycode == K_UP  || keycode == K_DOWN
		|| keycode == K_LEFT || keycode == K_RIGHT)
		translate_pos(dt, keycode);
	if (keycode == K_W || keycode == K_A || keycode == K_S || keycode == K_D)
		rotate_camera(dt, keycode);
	if (keycode == K_I || keycode == K_O || keycode == K_P)
		set_lighting(dt, keycode);
	dt->camera->norm_vect = norm_v(dt->camera->norm_vect);
	if (is_valid_keycode(keycode))
		update_parameters(dt);
}
