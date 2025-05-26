/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcologne <jcologne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:52:54 by jcologne          #+#    #+#             */
/*   Updated: 2025/05/16 16:13:38 by jcologne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "philo.h"

static bool	check_philo_death(t_data *data, int i)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&data->monitor_lock);
	time_since_last_meal = get_time() - data->philos[i].last_meal;
	if (time_since_last_meal > data->die_time)
	{
		data->end_sim = true;
		printf("%ld %d died\n",
			get_time() - data->start_time, data->philos[i].id + 1);
		pthread_mutex_unlock(&data->monitor_lock);
		return (true);
	}
	pthread_mutex_unlock(&data->monitor_lock);
	return (false);
}

static bool	check_all_ate(t_data *data)
{
	int		i;
	bool	all_ate;

	if (data->meals_limit == -1)
		return (false);
	all_ate = true;
	i = 0;
	while (i < data->philos_nbr)
	{
		pthread_mutex_lock(&data->monitor_lock);
		if (data->philos[i].meals_eaten < data->meals_limit)
			all_ate = false;
		pthread_mutex_unlock(&data->monitor_lock);
		if (!all_ate)
			break ;
		i++;
	}
	if (all_ate)
	{
		pthread_mutex_lock(&data->monitor_lock);
		data->end_sim = true;
		pthread_mutex_unlock(&data->monitor_lock);
	}
	return (all_ate);
}

void	*monitor_philos(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	if (!data || !data->philos)
		return (NULL);
	while (true)
	{
		i = 0;
		while (i < data->philos_nbr)
		{
			if (check_philo_death(data, i))
				return (NULL);
			i++;
		}
		if (check_all_ate(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
