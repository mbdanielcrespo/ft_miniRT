/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:29:39 by danalmei          #+#    #+#             */
/*   Updated: 2024/05/22 01:44:42 by feden-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

int	main(int ac, char **av)
{
	static t_data	*ptr;

	ptr = data();
	if (ac == 2)
	{
		init_data(av);
		print_data();
		mlx_setup();
		mlx_loop(ptr->mlx_ptr);
		data_destroy();
	}
	else
		ft_error("Invalid number of arguments!");
	return (0);
}
