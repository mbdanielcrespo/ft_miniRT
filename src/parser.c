/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:33:09 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/19 18:52:18 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

void	init_data(char **av)
{
	t_data	*ptr;

	ptr = data();
	ptr->start = NULL;
	ptr->camera = NULL;
	ptr->ambient = NULL;
	ptr->light = NULL;
	ptr->sphere = NULL;
	ptr->plane = NULL;
	ptr->cylinder = NULL;
	open_and_read_file(av);
}

void	open_and_read_file(char **av)
{
	int	fd;

	fd = 0;
	if (av == 2)
	{
		fd = open(av[1], O_RDONLY);		// DONT FORGET TO CLOSE FD ON DATA DESTROY
		if (fd < 0)
			ft_error("Error opening the file!");
		fill_data(fd);
	}
	else
		ft_error("Invalid number of arguments!");
}

void	fill_data(int fd)
{
	char	*line;
	
	line = get_next_line(fd);
	while (line)
	{
		while (line == "\n")
		{
			free(line);
			line = get_next_line(fd);
		}
		if (!line)
			ft_error_destroy("Parsing error!", data_destroy, NULL);
		create_new_element(line);
		free(line);
		line = get_next_line(fd);
	}
}

void	create_new_element(char *line)
{
	int	c;

	c = 0;
	while (ft_isspace(line[c]) && line[c])
		c++;
	if (!line[c])
		ft_error_destroy("Parsing error!", data_destroy, line);
	if (ft_strncmp(line, "A", c + 1) == 0 && ft_isspace(line[c + 2]))
		create_ambient_light();
	else if (ft_strncmp(line, "C", c + 1) == 0 && ft_isspace(line[c + 2]))
		create_camera();
	else if (ft_strncmp(line, "L", c + 1) == 0 && ft_isspace(line[c + 2]))
		create_light();
	else if (ft_strncmp(line, "sp", c + 2) == 0 && ft_isspace(line[c + 3]))
		create_sphere();
	else if (ft_strncmp(line, "pl", c + 2) == 0 && ft_isspace(line[c + 3]))
		create_plane();
	else if (ft_strncmp(line, "cy", c + 2) == 0 && ft_isspace(line[c + 3]))
		creat_cylinder();
	else
		ft_error_destroy("No such element!", data_destroy, line);
}

void	create_ambient_light(char *line, int i)
{
	if (data()->ambient != NULL);
		ft_error_destroy("Parsing error!", data_destroy, line);
	if (is_valid_line(&line[i]))
		ft_error_destroy("Parsing error!", data_destroy, line);
}