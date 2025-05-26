/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcologne <jcologne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:33:12 by jcologne          #+#    #+#             */
/*   Updated: 2025/05/26 20:39:33 by jcologne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fill_data(t_data *data, char **av)
{
	data->philos_nbr = ft_atol(av[1]);
	data->die_time = ft_atol(av[2]);
	data->eat_time = ft_atol(av[3]);
	data->sleep_time = ft_atol(av[4]);
	data->meals_limit = -1;
	if (av[5])
		data->meals_limit = ft_atol(av[5]);
	data->start_time = get_time();
	data->end_sim = false;
	pthread_mutex_init(&data->monitor_lock, NULL);
}

static void	init_forks(t_data *data, t_philo **philos)
{
	int	left;
	int	right;
	int	i;

	i = 0;
	while (i < data->philos_nbr)
	{
		left = i;
		right = (i + 1) % data->philos_nbr;
		if (i % 2 == 0)
		{
			(*philos)[i].left_fork = &data->forks[left];
			(*philos)[i].right_fork = &data->forks[right];
		}
		else
		{
			(*philos)[i].right_fork = &data->forks[right];
			(*philos)[i].left_fork = &data->forks[left];
		}
		i++;
	}
}

void	init_philos(t_data *data, t_philo **philos)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * data->philos_nbr);
	data->philos = *philos;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philos_nbr);
	if (!data->forks)
		free(*philos);
	i = 0;
	while (i < data->philos_nbr)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			cleanup(data, *philos);
		(*philos)[i].id = i;
		(*philos)[i].data = data;
		(*philos)[i].last_meal = data->start_time;
		(*philos)[i].meals_eaten = 0;
		i++;
	}
	i = 0;
	init_forks(data, philos);
}
