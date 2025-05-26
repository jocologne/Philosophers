/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcologne <jcologne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:43:12 by jcologne          #+#    #+#             */
/*   Updated: 2025/05/26 20:34:17 by jcologne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	validate_arguments(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (false);
	i = 1;
	while (av[i])
	{
		if (!is_valid_number(av[i]) || ft_atol(av[i]) <= 0)
		{
			printf("Invalid argument: %s\n", av[i]);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	create_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->philos_nbr)
	{
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]) != 0)
			return (false);
		i++;
	}
	return (true);
}

static void	join_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->philos_nbr)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		*philos;
	pthread_t	monitor_thread;

	if (!validate_arguments(ac, av))
		return (1);
	fill_data(&data, av);
	init_philos(&data, &philos);
	if (!create_threads(&data, philos))
	{
		cleanup(&data, philos);
		return (1);
	}
	if (pthread_create(&monitor_thread, NULL, monitor_philos, &data) != 0)
	{
		cleanup(&data, philos);
		return (1);
	}
	join_threads(&data, philos);
	pthread_join(monitor_thread, NULL);
	cleanup(&data, philos);
	return (0);
}
