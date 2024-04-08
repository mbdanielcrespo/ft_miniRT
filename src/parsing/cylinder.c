/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:00:55 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/28 10:34:53 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

void	create_cylinder(char *line, int n_args)
{
	char		**args;
	t_cylinder	*cy;

	if (!is_valid_line(line, n_args))
		ft_error_destroy("Parsing error, invalid line", data_destroy);
	cy = ft_safe_malloc(sizeof(t_cylinder), data_destroy, NULL);
	cy->next = NULL;
	cy->position = ft_safe_malloc(sizeof(t_xyz), data_destroy, NULL);
	cy->norm_vect = ft_safe_malloc(sizeof(t_xyz), data_destroy, NULL);
	cy->color = ft_safe_malloc(sizeof(t_rgb), data_destroy, NULL);
	args = ft_split(line, ' ');
	cy->diameter = ft_atof(args[3]);
	cy->height = ft_atof(args[4]);
	if (!triple_float(cy->position, args[1]) ||
			!triple_float(cy->norm_vect, args[2]) ||
			!triple_int(cy->color, args[5]))
	{
		ft_fsplit(args);
		ft_error_destroy("Parsing error, on args!", data_destroy);
	}
	ft_fsplit(args);
	insert_cylinder(cy);
	printf("New cylinder created\n");
}

void	insert_cylinder(t_cylinder *cy)
{
	t_cylinder	*tmp;

	tmp = data()->cylinder; 
	if (!tmp)
	{
		data()->cylinder = cy;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = cy;
}
