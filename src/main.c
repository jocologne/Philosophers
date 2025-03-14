/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcologne <jcologne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:43:12 by jcologne          #+#    #+#             */
/*   Updated: 2025/03/10 19:27:42 by jcologne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	validate_arguments(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (printf("Wrong number of arguments\n"));
	while (av[i])
	{
		if (alpha(av[i]) || ft_atol(av[i]) <= 0 || ft_atol(av[i]) > INT_MAX)
			return (printf("Wrong argument\n"));
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (validate_arguments(ac, av))
		return (1);
	input_data(&data, av);
}
