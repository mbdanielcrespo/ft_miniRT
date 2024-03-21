/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:21:56 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/21 17:24:38 by danalmei         ###   ########.fr       */
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
	ptr->camera = NULL;
	ptr->ambient = NULL;
	ptr->light = NULL;
	ptr->sphere = NULL;
	ptr->plane = NULL;
	ptr->cylinder = NULL;
	//printf("Data initialized\n");
	open_and_read_file(av);
}

void	open_and_read_file(char **av)
{
	int	fd;

	fd = open(av[1], O_RDONLY);		// DONT FORGET TO CLOSE FD ON DATA DESTROY
	if (fd < 0)
		ft_error("Error opening the file!");
	//printf("File opend\n");
	fill_data(fd);
}

void	fill_data(int fd)
{
	char	*line;
	
	line = get_next_line(fd);
	while (line)
	{
		while (line && line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
		}
		if (!line)
			ft_error_destroy("Parsing error!", data_destroy);
		data()->current_line = line;
		create_new_element(line);
		free(line);
		line = get_next_line(fd);
	}
}
