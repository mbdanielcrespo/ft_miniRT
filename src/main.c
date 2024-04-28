/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:29:39 by danalmei          #+#    #+#             */
/*   Updated: 2024/04/28 20:59:56 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

int	main(int ac, char **av)
{
	t_data	*ptr;

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
