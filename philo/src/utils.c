/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcologne <jcologne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:09:28 by jcologne          #+#    #+#             */
/*   Updated: 2025/05/16 16:25:19 by jcologne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_valid_number(char *str)
{
	if (*str == '\0')
		return (false);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

long	ft_atol(const char *n)
{
	int	sign;
	long	num;
	int	i;

	i = 0;
	sign = 1;
	num = 0;
	if (n[i] == '\0')
		return (0);
	while ((n[i] >= 9 && n[i] <= 13) || n[i] == 32)
		i++;
	if (n[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (n[i] == '+')
		i++;
	while (n[i] >= '0' && n[i] <= '9')
	{
		num = (num * 10) + (n[i] - '0');
		i++;
	}
	return (num * sign);
}

void	print_status(t_philo *philo, char *status)
{
	long	time;

	pthread_mutex_lock(&philo->data->monitor_lock);
	if (!philo->data->end_sim)
	{
		time = get_time() - philo->data->start_time;
		printf("%ld %d %s\n", time, philo->id + 1, status);
	}
	pthread_mutex_unlock(&philo->data->monitor_lock);
}

bool	check_sim_end(t_data *data)
{
	bool	end_sim;

	pthread_mutex_lock(&data->monitor_lock);
	end_sim = data->end_sim;
	pthread_mutex_unlock(&data->monitor_lock);
	return (end_sim);
}

void	cleanup(t_data *data, t_philo *philos)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->philos_nbr)
			pthread_mutex_destroy(&data->forks[i++]);
		free(data->forks);
	}
	pthread_mutex_destroy(&data->monitor_lock);
	if (philos)
		free(philos);
}
