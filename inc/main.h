/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:38:13 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/19 18:19:18 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <libft.h>

typedef struct s_xyz		t_xyz;
typedef struct s_rgb		t_rgb;
typedef struct s_element	t_element;
typedef struct s_data		t_data;
typedef	enum e_type			t_type;

struct s_xyz
{
	float	x;
	float	y;
	float	z;
};

struct s_rgb
{
	int	r;
	int	g;
	int	b;
};

enum	e_type
{
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
};

struct s_element
{
	t_type		type;
	t_xyz		position;
	t_xyz		normal_vector;
	float		ratio;
	float		brightness;
	t_rgb		color;
	int			field_of_view;
	float		diameter;
	float		height;
	t_element	*next;
	t_element	*prev;
};

struct	s_data
{
	t_element	*start;
	t_camera	*camera;
	t_ambient	*ambient;
	t_light		*light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	
};

t_data	*data(void);
void	init_data(char **av);
void	fill_data(fd);

void	data_destroy(void);

#endif //MAIN_H