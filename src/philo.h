/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcologne <jcologne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:44:12 by jcologne          #+#    #+#             */
/*   Updated: 2025/05/16 16:34:38 by jcologne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	long					philos_nbr;
	long					die_time;
	long					eat_time;
	long					sleep_time;
	long					meals_limit;
	long					start_time;
	bool					end_sim;
	pthread_mutex_t	*forks;
	pthread_mutex_t	monitor_lock;
	t_philo				*philos;
}	t_data;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	t_data				*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long					last_meal;
	int					meals_eaten;
}	t_philo;

// UTILS
bool	is_valid_number(char *str);
long	ft_atol(const char *n);
void	print_status(t_philo *philo, char *status);
bool	check_sim_end(t_data *data);
void	cleanup(t_data *data, t_philo *philos);

// INIT
void	fill_data(t_data *data, char **av);
void	init_philos(t_data *data, t_philo **philos);

// TIME
long	get_time(void);
void	precise_usleep(long time_in_ms);

// ACTIONS
void	*routine(void *arg);

// MONITOR
void	*monitor_philos(void *arg);

#endif