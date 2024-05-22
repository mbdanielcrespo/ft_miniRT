/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:38:13 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/22 12:45:30 by danalmei         ###   ########.fr       */
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

# define W_WIDTH	500
# define W_HEIGHT	500
# define PI			3.14159265358979323846
# define EPSILON	0.001
# define K_DIFFUSE	0.4
# define ROT_STEP	0.1	
# define STEP		2.0
# define DEFAULT_DL	1
# define DEFAULT_SL	1
# define DEFAULT_HS 1
# define K_ESC		65307
# define K_UP		65362
# define K_DOWN		65364
# define K_LEFT		65361
# define K_RIGHT	65363
# define K_F		102
# define K_B		98
# define K_Z		122
# define K_I		105
# define K_O		111
# define K_P		112
# define K_W		119
# define K_A		97
# define K_S		115
# define K_D		100
# define K_1		49
# define K_2		50
# define K_3		51
# define K_4		52

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
typedef enum e_type			t_type;

enum	e_type
{
	SPHERE,
	PLANE,
	CYLINDER,
};

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
	t_rgb	color;
};

struct	s_camera
{
	t_xyz		position;
	t_xyz		norm_vect;
	t_dlong		field_of_view;
};

struct	s_light
{
	t_xyz		position;
	t_dlong		brightness;
	t_rgb		color;
};

struct s_sphere
{
	t_xyz		position;
	t_dlong		diameter;
	t_rgb		color;
	t_sphere	*next;
};

struct s_plane
{
	t_xyz		position;
	t_xyz		norm_vect;
	t_rgb		color;
	t_plane		*next;
};

struct s_cylinder
{
	t_xyz		position;
	t_xyz		norm_vect;
	t_dlong		diameter;
	t_dlong		height;
	t_rgb		color;
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

struct s_viewport
{
	t_dlong	view_ratio;
	t_dlong	ndc_x;
	t_dlong	ndc_y;
	t_dlong	scale;
	t_xyz	cam_forward;
	t_xyz	cam_up;
	t_xyz	cam_right;
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
	t_viewport		vp;
	int				diffuse_light;
	int				specular_light;
	int				hard_shadows;
	int				intersec;
	int				on_base;
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
void		free_spheres(t_sphere *sphere);
void		free_planes(t_plane *plane);
void		free_cylinders(t_cylinder *cylinder);
void		data_destroy(void);
// Debug prints
void		print_data(void);
void		print_trpl_float(t_xyz trpl_float);
void		print_trpl_int(t_rgb trpl_int);
void		print_ambient(t_ambient *ambient);
void		print_camera(t_camera *cam);
void		print_light(t_light *light);
void		print_spheres(t_sphere *sphere);
void		print_planes(t_plane *plane);
void		print_cylinders(t_cylinder *cylinder);

// Viewport
t_viewport	set_viewport(t_viewport vp, int x, int y);
t_xyz		calc_pixel_dir(t_viewport vp);
void		draw_viewport(t_data *dt);

// Paint Pixel
t_rgb		calculate_color(t_xyz ip, void *obj, t_type type);
int			calc_shadow(t_data *dt, t_xyz ip, void *obj, t_type type);
void		paint_pixel(int pixel, t_rgb color, int color_flag);

// Object Intersections
int			update_dist(void *obj, t_xyz *ip, double *min_dist, int *intersec);
void		object_intersections(t_data *dt, t_xyz pixel_dir,
				int pixel, int intersec);
void		object_intersection2(t_xyz pixel_dir, int *intersec,
				void *obj, t_xyz shadow_origin);
// sp
t_sphere	*intersect_shperes(t_data *dt, t_xyz pix_dir, t_xyz *intersect_pt);
int			intersect_sphere(t_xyz pos, t_xyz pix_dir,
				t_sphere *sp, t_xyz *intersect_pt);
// pl
t_plane		*intersect_planes(t_data *dt, t_xyz pix_dir,
				t_xyz *intersect_pt);
int			intersect_plane(t_xyz pos, t_xyz pix_dir,
				t_plane *pl, t_xyz *intersect_pt);
// cy
int			within_cylinder_radius(t_xyz *intersect_pt, t_cylinder *cy,
				t_xyz cap_center, double *min_dist);
int			within_cylinder_tube(t_cylinder *cy, t_xyz *intersect_pt,
				double *min_dist);
int			solve_cylinder(t_xyz pos, t_xyz pix_dir,
				t_cylinder *cy, t_xyz *intersect_pt);
t_cylinder	*intersect_cylinders(t_data *dt, t_xyz pix_dir,
				t_xyz *intersect_pt);
int			intersect_cylinder(t_xyz pos, t_xyz pix_dir,
				t_cylinder *cy, t_xyz *intersect_pt);
int			intersect_shperes2(t_data *dt, t_xyz pix_dir, t_xyz *ip,
				t_xyz shadow_origin);
int			intersect_planes2(t_data *dt, t_xyz pix_dir, t_xyz *ip);
int			intersect_cylinders2(t_data *dt, t_xyz pix_dir, t_xyz *ip,
				t_xyz shadow_origin);
int			intersect_sphere_shade(t_xyz pos, t_xyz pix_dir, t_sphere *sp,
				t_xyz *ip);
int			intersect_plane_shade(t_xyz pos, t_xyz pix_dir, t_plane *pl,
				t_xyz *ip);
int			solve_cylinder_shade(t_xyz pos, t_xyz pix_dir, t_cylinder *cy,
				t_xyz *ip);
int			intersect_cylinder_shade(t_xyz pos, t_xyz pix_dir, t_cylinder *cy,
				t_xyz *ip);

///////////// CALCULUS //////////
// Color
void		set_pos_and_col(t_rgb *col, t_xyz *pos, void *obj, t_type type);
t_rgb		base_color(t_data *dt, void *obj, t_type type);
t_rgb		set_color(t_light *lig, t_rgb base_col, double diffuse_intensity);
t_rgb		scale_color(t_rgb color, double scale);
t_rgb		add_color(t_rgb color1, t_rgb color2);

// Light
void		set_normal(t_xyz *normal, void *obj, t_type type, t_xyz ip);
t_rgb		lit_color(t_data *dt, t_xyz intersect_pt, void *obj, t_type type);
t_rgb		specular_light(t_data *dt, t_xyz ip, t_xyz normal,
				double shininess);
t_xyz		reflect_v(t_xyz light_dir, t_xyz normal);

// Vector math
t_xyz		norm_v(t_xyz v);
t_xyz		add_v(t_xyz v1, t_xyz v2);
t_xyz		subtr_v(t_xyz v1, t_xyz v2);
t_xyz		mult_v(t_xyz v, double scalar);
double		dot(t_xyz v1, t_xyz v2);
t_xyz		cross_v(t_xyz v1, t_xyz v2);

///////////// UTILS /////////////
// Validate
int			triple_int(t_rgb *trpl_int, char *arg);
int			triple_float(t_xyz *trpl_float, char *arg);
int			is_valid_char(char ch);
int			is_valid_arg(char *arg);
int			is_valid_line(char *line, int n_args);
int			check_rgb(t_rgb *tmp);
// mlx setup
void		update_parameters(t_data *dt);
int			key_press(int keycode);
int			close_win(void);
void		mlx_setup(void);
// Utils
double		deg_to_rad(double deg);
double		distance(t_xyz p1, t_xyz p2);
// Camera mov
int			is_valid_keycode(int keycode);
void		set_lighting(t_data *dt, int keycode);
void		translate_pos(t_data *dt, int keycode);
void		camera_settings(t_data *dt, int keycode);
// Camera rot
void		update_camera_vectors(t_data *dt);
void		rot_yaw_x(t_data *dt, double delta);
void		rot_pitch_y(t_data *dt, double delta);
void		rotate_camera(t_data *dt, int keycode);

#endif //MAIN_H
