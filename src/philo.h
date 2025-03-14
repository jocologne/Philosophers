/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcologne <jcologne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:44:12 by jcologne          #+#    #+#             */
/*   Updated: 2025/03/10 18:00:36 by jcologne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_data
{
	long	philos_nbr;
	long	die_time;
	long	eat_time;
	long	sleep_time;
	long	meals_limit;
	long	start_time;
	int		end_sim;
	//TODO
}	t_data;

//UTILS
int		alpha(char *str);
long	ft_atol(const char *n);

//INIT
void	input_data(t_data *data, char **av);

#endif