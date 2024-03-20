/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:33:09 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/20 18:46:57 by danalmei         ###   ########.fr       */
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
		ft_error_destroy("Parsing error!", data_destroy, line);
	if (ft_strncmp(&line[c], "A", 1) == 0 && ft_isspace(line[c + 1]))
		create_ambient_light(line, 3);
	/*else if (ft_strncmp(line, "C", c + 1) == 0 && ft_isspace(line[c + 1]))
		create_camera();
	else if (ft_strncmp(line, "L", c + 1) == 0 && ft_isspace(line[c + 1]))
		create_light();
	else if (ft_strncmp(line, "sp", c + 2) == 0 && ft_isspace(line[c + 2]))
		create_sphere();
	else if (ft_strncmp(line, "pl", c + 2) == 0 && ft_isspace(line[c + 2]))
		create_plane();
	else if (ft_strncmp(line, "cy", c + 2) == 0 && ft_isspace(line[c + 2]))
		creat_cylinder();
	else
		ft_error_destroy("No such element!", data_destroy, line);*/
}

void	create_ambient_light(char *line, int n_args)
{
	char		**args;
	t_ambient	*A;
	
	A = data()->ambient;
	A = malloc(sizeof(t_ambient));
	if (data()->ambient != NULL)
		ft_error_destroy("Parsing error!", data_destroy, line);
	if (!is_valid_line(line, n_args))
		ft_error_destroy("Parsing error!", data_destroy, line);
	args = ft_split(line, ' ');
	A->intensity = ft_atof(args[2]);
	if (!triple_int(A->color, args[3]))
	{
		ft_fsplit(args);
		ft_error_destroy("Parsing error!", data_destroy, line);
	}
	printf("New element created\n");

}
