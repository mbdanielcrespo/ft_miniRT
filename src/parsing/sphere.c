/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:54:58 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/20 14:12:30 by feden-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

void	create_sphere(char *line, int n_args)
{
	char		**args;
	t_sphere	*sp;

	if (!is_valid_line(line, n_args))
		ft_error_destroy("Parsing error, invalid line", data_destroy);
	sp = ft_safe_malloc(sizeof(t_sphere), data_destroy, NULL);
	sp->next = NULL;
	args = ft_split(line, ' ');
	sp->diameter = ft_atof(args[2]);
	if (sp->diameter < 0 || !triple_float(&sp->position, args[1])
		|| !triple_int(&sp->color, args[3]))
	{
		ft_fsplit(args);
		ft_error_destroy("Parsing error on args!", data_destroy);
	}
	ft_fsplit(args);
	insert_sphere(sp);
	printf("New sphere created\n");
}

void	insert_sphere(t_sphere *sp)
{
	t_sphere	*tmp;

	tmp = data()->sphere;
	if (!tmp)
	{
		data()->sphere = sp;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = sp;
}
