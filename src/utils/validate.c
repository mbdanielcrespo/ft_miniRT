/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:48:59 by danalmei          #+#    #+#             */
/*   Updated: 2024/04/28 21:30:05 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

int	triple_int(t_rgb *trpl_int, char *arg)
{
	char	**vals;

	vals = ft_split(arg, ',');
	if (!vals[0] || !vals[1] || !vals[2])
	{
		ft_fsplit(vals);
		return (0);
	}
	trpl_int->r = ft_atoi(vals[0]);
	trpl_int->g = ft_atoi(vals[1]);
	trpl_int->b = ft_atoi(vals[2]);
	ft_fsplit(vals);
	return (1);
}

int	triple_float(t_xyz *trpl_float, char *arg)
{
	char	**vals;

	vals = ft_split(arg, ',');
	if (!vals[0] || !vals[1] || !vals[2])
	{
		ft_fsplit(vals);
		return (0);
	}
	trpl_float->x = ft_atof(vals[0]);
	trpl_float->y = ft_atof(vals[1]);
	trpl_float->z = ft_atof(vals[2]);
	ft_fsplit(vals);
	return (1);
}

int	is_valid_line(char *line, int n_args)
{
	int		c;
	char	**args;

	c = 1;
	args = ft_split(line, ' ');
	while (args[c])
	{
		if (!is_valid_arg(args[c]))
		{
			ft_fsplit(args);
			return (0);
		}
		c++;
	}
	if (c != n_args)
	{
		printf("Invalid number of arguments at line:\n%s\n", line);
		ft_fsplit(args);
		return (0);
	}
	ft_fsplit(args);
	printf("Line is valid!\n");
	return (1);
}

int	is_valid_arg(char *arg)
{
	int	c;

	c = 0;
	if (!arg || !*arg)
		return (0);
	while (arg[c] && arg[c] != '\n')
	{
		if (!is_valid_char(arg[c]))
		{
			printf("Invalid argument at arg:\n%s\n", arg);
			return (0);
		}
		c++;
	}
	return (1);
}

int	is_valid_char(char ch)
{
	if (ft_isdigit(ch) || ch == '-'
		|| ch == '.' || ch == ',')
		return (1);
	return (0);
}
