/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:33:09 by danalmei          #+#    #+#             */
/*   Updated: 2024/04/25 16:01:03 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

void	create_new_element(char *line)
{
	int	c;

	c = 0;
	while (ft_isspace(line[c]) && line[c])
		c++;
	if (!line[c])
		ft_error_destroy("Parsing error!", data_destroy);
	if (ft_strncmp(&line[c], "A", 1) == 0 && ft_isspace(line[c + 1]))
		create_ambient(line, 3);
	else if (ft_strncmp(&line[c], "C", 1) == 0 && ft_isspace(line[c + 1]))
		create_camera(line, 4);
	else if (ft_strncmp(&line[c], "L", 1) == 0 && ft_isspace(line[c + 1]))
		create_light(line, 4);
	else if (ft_strncmp(&line[c], "sp", 2) == 0 && ft_isspace(line[c + 2]))
		create_sphere(line, 4);
	else if (ft_strncmp(&line[c], "pl", 2) == 0 && ft_isspace(line[c + 2]))
		create_plane(line, 4);
	else if (ft_strncmp(&line[c], "cy", 2) == 0 && ft_isspace(line[c + 2]))
		create_cylinder(line, 6);
	else
	{
		printf("At line: %s\n", line);
		ft_error_destroy("No such element!", data_destroy);
	}
}

void	create_ambient(char *line, int n_args)
{
	char		**args;
	t_ambient	*A;
	
	if (data()->ambient != NULL)
		ft_error_destroy("Parsing error, light exists", data_destroy);
	if (!is_valid_line(line, n_args))
		ft_error_destroy("Parsing error, invalid line", data_destroy);
	A = ft_safe_malloc(sizeof(t_ambient), data_destroy, NULL);
	args = ft_split(line, ' ');
	A->intensity = ft_atof(args[1]);
	if (!triple_int(&A->color, args[2]))
	{
		ft_fsplit(args);
		ft_error_destroy("Parsing error, on args!", data_destroy);
	}
	ft_fsplit(args);
	data()->ambient = A;
	printf("New ambient created\n");
}
void	create_camera(char *line, int n_args)
{
	char		**args;
	t_camera	*C;

	if (data()->camera != NULL)
		ft_error_destroy("Parsing error, camera exists", data_destroy);
	if (!is_valid_line(line, n_args))
		ft_error_destroy("Parsing error, Invalid line!", data_destroy);
	C = ft_safe_malloc(sizeof(t_camera), data_destroy, NULL);
	args = ft_split(line, ' ');
	C->field_of_view = ft_atof(args[3]);
	if (!triple_float(&C->position, args[1]) ||
			!triple_float(&C->norm_vect, args[2]))
	{
		ft_fsplit(args);
		ft_error_destroy("Parsing error, on args!", data_destroy);
	}
	ft_fsplit(args);
	data()->camera = C;
	printf("New camera created\n");
}

void	create_light(char *line, int n_args)
{
	char		**args;
	t_light		*L;

	if (data()->light != NULL)
		ft_error_destroy("Parsing error, light exists", data_destroy);
	if (!is_valid_line(line, n_args))
		ft_error_destroy("Parsing error, invalid line", data_destroy);
	L = ft_safe_malloc(sizeof(t_light), data_destroy, NULL);
	args = ft_split(line, ' ');
	L->brightness = ft_atof(args[2]);
	if (!triple_float(&L->position, args[1]) ||
			!triple_int(&L->color, args[3]))
	{
		ft_fsplit(args);
		ft_error_destroy("Parsing error on args!", data_destroy);
	}
	ft_fsplit(args);
	data()->light = L;
	printf("New light created\n");
}
