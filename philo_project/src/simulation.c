/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:11:41 by aimokhta          #+#    #+#             */
/*   Updated: 2025/07/02 10:35:35 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_simulation(t_data *data)
{
	if (create_philo(data, &data->philo) == 1)
		return (1);
	if (pthread_create(data, NULL, &monitor_routine, NULL) == 1)
		return (1);
	if (join_philo(&data->philo) == 1)
		return (1);
	if (pthread_join(data, NULL) == 1)
		return (1);
}

static int	create_philo(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < data->arg.num_of_philo)
	{
		if (pthread_create(data->philo[i].thread, NULL, \
&philo_routine, &data) == 1)
			return (1);
	}
	return (0);
}

void	*philo_routine(void *arg)
{
	t_data *data;

	data = (t_data *)arg;
	pthread_mutex_init(&data->, NULL);

}

void	*monitor_routine(void *arg)
{
	
}