/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:19:41 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/20 14:56:29 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

void	update_camera_vectors(t_data *dt)
{
	t_xyz	world_up;

	world_up.x = 0;
	world_up.y = 1;
	world_up.z = 0;
	dt->vp.cam_right = norm_v(cross_v(world_up, dt->camera->norm_vect));
	dt->vp.cam_up = norm_v(cross_v(dt->camera->norm_vect, dt->vp.cam_right));
}

void	rot_yaw_x(t_data *dt, double delta)
{
	t_xyz	old_forward;

	old_forward = dt->camera->norm_vect;
	dt->camera->norm_vect.x = cos(delta) * old_forward.x
		+ sin(delta) * old_forward.z;
	dt->camera->norm_vect.z = -sin(delta) * old_forward.x
		+ cos(delta) * old_forward.z;
	update_camera_vectors(dt);
}

void	rot_pitch_y(t_data *dt, double delta)
{
	t_xyz	old_forward;

	old_forward = dt->camera->norm_vect;
	dt->camera->norm_vect.y = cos(delta) * old_forward.y
		- sin(delta) * old_forward.z;
	dt->camera->norm_vect.z = sin(delta) * old_forward.y
		+ cos(delta) * old_forward.z;
	update_camera_vectors(dt);
}

void	rotate_camera(t_data *dt, int keycode)
{
	if (keycode == K_W)
		rot_pitch_y(dt, -ROT_STEP);
	else if (keycode == K_S)
		rot_pitch_y(dt, ROT_STEP);
	else if (keycode == K_A)
		rot_yaw_x(dt, -ROT_STEP);
	else if (keycode == K_D)
		rot_yaw_x(dt, ROT_STEP);
}
