/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcologne <jcologne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:07:33 by jcologne          #+#    #+#             */
/*   Updated: 2025/05/27 22:43:55 by jcologne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "philo.h"

void	precise_usleep(long time_in_ms)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time();
	while (1)
	{
		elapsed = get_time() - start;
		remaining = time_in_ms - elapsed;
		if (remaining <= 0)
			break ;
		if (remaining > 10)
			usleep(remaining * 50);
		else
			usleep(remaining * 10);
	}
}

static bool	take_forks(t_philo *philo)
{
	if (check_sim_end(philo->data))
		return (false);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		if (philo->data->philos_nbr == 1)
		{
			pthread_mutex_unlock(philo->left_fork);
			precise_usleep(philo->data->die_time * 2);
			return (false);
		}
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	return (true);
}

static void	update_meal_info(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->monitor_lock);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->monitor_lock);
}

static void	eat_sleep_think(t_philo *philo)
{
	if (philo->meals_eaten < philo->data->meals_limit)
		print_status(philo, "is eating");
	update_meal_info(philo);
	precise_usleep(philo->data->eat_time);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_status(philo, "is sleeping");
	precise_usleep(philo->data->sleep_time);
	print_status(philo, "is thinking");
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_usleep(10);
	while (!check_sim_end(philo->data))
	{
		if (!take_forks(philo))
			break ;
		eat_sleep_think(philo);
	}
	return (NULL);
}
