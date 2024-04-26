/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:00:29 by danalmei          #+#    #+#             */
/*   Updated: 2024/04/26 11:48:36 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

void	create_plane(char *line, int n_args)
{
	char	**args;
	t_plane	*pl;

	if (!is_valid_line(line, n_args))
		ft_error_destroy("Parsing error, invalid line", data_destroy);
	pl = ft_safe_malloc(sizeof(t_plane), data_destroy, NULL);
	pl->next = NULL;
	args = ft_split(line, ' ');
	if (!triple_float(&pl->position, args[1]) ||
			!triple_float(&pl->norm_vect, args[2]) ||
			!triple_int(&pl->color, args[3]))
	{
		ft_fsplit(args);
		ft_error_destroy("Parsing error, on args", data_destroy);
	}
	ft_fsplit(args);
	insert_plane(pl);
	printf("New plane created\n");
}

void	insert_plane(t_plane *pl)
{
	t_plane	*tmp;

	tmp = data()->plane; 
	if (!tmp)
	{
		data()->plane = pl;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = pl;
}
