/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:38:13 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/20 18:35:41 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <libft.h>

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define BLUE    "\x1b[34m"
# define L_RED   "\x1b[91m"
# define L_GREEN "\x1b[92m"
# define L_BLUE  "\x1b[94m"
# define WHITE   "\x1b[97m"
 
typedef struct s_xyz		t_xyz;
typedef struct s_rgb		t_rgb;
typedef struct s_element	t_element;
typedef struct s_data		t_data;
typedef	enum e_type			t_type;
typedef struct s_camera		t_camera;
typedef struct s_ambient	t_ambient;
typedef struct s_light		t_light;
typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;

struct s_xyz
{
	t_dlong	x;
	t_dlong	y;
	t_dlong	z;
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

struct	s_ambient
{
	t_dlong	intensity;
	t_rgb	*color;
};

struct	s_camera
{
	t_xyz		*position;
	t_xyz		*norm_vect;
	t_dlong		field_of_view;
};

struct	s_light
{
	t_xyz		*position;
	t_dlong		brightness;
	t_rgb		*color;
};

struct s_sphere
{
	t_xyz		*position;
	t_dlong		diameter;
	t_rgb		*color;
	t_sphere	*next;
};

struct s_plane
{
	t_xyz		*position;
	t_xyz		*norm_vect;
	t_rgb		*color;
	t_plane		*next;
};

struct s_cylinder
{
	t_xyz		*position;
	t_xyz		*norm_vect;
	t_dlong		diameter;
	t_dlong		height;
	t_rgb		*color;
	t_cylinder	*next;
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
void	open_and_read_file(char **av);
void	fill_data(int fd);

void	create_new_element(char *line);
void	create_ambient_light(char *line, int n_args);

int		triple_int(t_rgb *trpl_int, char *arg);
int		triple_float(t_xyz *trpl_float, char *arg);
int		is_valid_char(char ch);
int		is_valid_arg(char *arg);
int		is_valid_line(char *line, int n_args);

void	print_data(void);
void	print_trpl_float(t_xyz *trpl_float);
void	print_trpl_int(t_rgb *trpl_int);
void	print_ambient(t_ambient *ambient);
void	print_camera(t_camera *cam);
void	print_light(t_light *light);
void	print_spheres(t_sphere *sphere);
void	print_planes(t_plane *plane);
void	print_cylinders(t_cylinder *cylinder);

void	data_destroy(void);

#endif //MAIN_H