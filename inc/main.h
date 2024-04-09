/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:38:13 by danalmei          #+#    #+#             */
/*   Updated: 2024/04/09 21:53:19 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <libft.h>
# include <math.h> 
# include <mlx.h>

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define BLUE		"\x1b[34m"
# define YELLOW		"\x1b[33m"
# define PURPLE		"\x1b[35m"
# define L_RED		"\x1b[91m"
# define L_GREEN	"\x1b[92m"
# define L_BLUE		"\x1b[94m"
# define L_YELLOW	"\x1b[93m"
# define L_PURPLE	"\x1b[95m"
# define WHITE		"\x1b[97m"

# define W_WIDTH	400
# define W_HEIGHT	400
# define PI			3.14159265358979323846
# define K_DIFFUSE	0.8

# define K_ESC		65307
# define K_UP		65362
# define K_DOWN		65364
# define K_LEFT		65361
# define K_RIGHT	65363
# define K_1		49
# define K_2		50
# define K_3		51
# define K_4		52

# define BPP2		32								// RGBA (with Alpha chanel)
# define BPP		24								// RGB
# define LINE_SIZE	(W_WIDTH / (BPP / 8))			// No padding assumed
# define L_ENDIAN	0								// LSByte stored in the smallest memory address
# define B_ENDIAN	1								// MSByte stored in the smallest memory address
 
typedef struct s_xyz		t_xyz;
typedef struct s_rgb		t_rgb;
typedef struct s_element	t_element;
typedef struct s_data		t_data;
typedef struct s_camera		t_camera;
typedef struct s_ambient	t_ambient;
typedef struct s_light		t_light;
typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;
typedef struct s_viewport	t_viewport;
typedef struct s_img		t_img;

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

struct s_img
{
	void			*img_ptr;
	unsigned char	*img_data;
	int				bpp;
	int				line_size;
	int				endian;
};

struct	s_data
{
	t_camera		*camera;
	t_ambient		*ambient;
	t_light			*light;
	t_sphere		*sphere;
	t_plane			*plane;
	t_cylinder		*cylinder;
	char			*current_line;
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			img;
	//int				width;
	//int				height;
};



struct s_viewport
{
	t_dlong	view_ratio;
	t_dlong	ndcX;
	t_dlong	ndcY;
	t_dlong	scale;
	t_xyz	camUp;
	t_xyz	camRight;
};


// Data
t_data		*data(void);
void		init_data(char **av);
void		open_and_read_file(char **av);
void		fill_data(int fd);

// Create elements
void		create_new_element(char *line);
void		create_ambient(char *line, int n_args);
void		create_camera(char *line, int n_args);
void		create_light(char *line, int n_args);
void		create_sphere(char *line, int n_args);
void		insert_sphere(t_sphere *sp);
void		create_plane(char *line, int n_args);
void		insert_plane(t_plane *pl);
void		create_cylinder(char *line, int n_args);
void		insert_cylinder(t_cylinder *cy);

// Cleanup
void		free_ambient(t_ambient *ambient);
void		free_camera(t_camera *camera);
void		free_light(t_light *light);
void		free_spheres(t_sphere *sphere);
void		free_planes(t_plane *plane);
void		free_cylinders(t_cylinder *cylinder);
void		data_destroy(void);

// Debug prints
void		print_data(void);
void		print_trpl_float(t_xyz *trpl_float);
void		print_trpl_int(t_rgb *trpl_int);
void		print_ambient(t_ambient *ambient);
void		print_camera(t_camera *cam);
void		print_light(t_light *light);
void		print_spheres(t_sphere *sphere);
void		print_planes(t_plane *plane);
void		print_cylinders(t_cylinder *cylinder);

// Viewport
t_viewport	set_viewport(t_viewport vp, int x, int y);
t_xyz		calc_pixel_dir(t_viewport vp);
t_rgb		lit_color_sp(t_data *dt, t_rgb base_col, t_xyz *intersect_pt, t_sphere *sp);
t_rgb		lit_color_cy(t_data *dt, t_rgb base_col, t_xyz *intersect_pt, t_cylinder *cy);
t_rgb		base_color(t_data *dt, t_rgb starting_col);

void		draw_on_screen(t_data *dt, t_xyz pixel_dir, int pixel);
void		draw_viewport(t_data *dt);

// Intersections
void		object_intersections(t_data *dt, t_xyz pixel_dir, int pixel);
double		intersect_plane_2(t_xyz pos, t_xyz pix_dir, t_plane *pl, t_xyz *intersect_pt);
double 		intersect_plane(t_xyz pos, t_xyz pix_dir, t_xyz plane_point, t_xyz plane_normal);
int			intersect_sphere(t_xyz pos, t_xyz pix_dir, t_sphere *sp, t_xyz *intersect_pt);

double		intersect_cylinder(t_xyz pos, t_xyz pix_dir, t_cylinder *cy, t_xyz *intersect_pt);
///////////// UTILS /////////////
// Validate
int			triple_int(t_rgb *trpl_int, char *arg);
int			triple_float(t_xyz *trpl_float, char *arg);
int			is_valid_char(char ch);
int			is_valid_arg(char *arg);
int			is_valid_line(char *line, int n_args);

// mlx setup
int			key_press(int keycode);
int 		close_win(void);
void		mlx_setup(void);

// Utils
double		deg_to_rad(double deg);

// Vector math
t_xyz		normalizeV(t_xyz v);
t_xyz		addV(t_xyz v1, t_xyz v2);
t_xyz		subtractV(t_xyz v1, t_xyz v2);
t_xyz		multiplyV(t_xyz v, double scalar);
double		multiplyVs(t_xyz v1, t_xyz v2);

#endif //MAIN_H