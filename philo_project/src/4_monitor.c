/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_monitor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:13:39 by aimokhta          #+#    #+#             */
/*   Updated: 2025/08/07 18:12:16 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg);
static bool	did_anyone_died(t_data *data);
static bool	did_everyone_eat_enough(t_data *data);

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		usleep(2000);
		if (did_anyone_died(data) == true)
			return (NULL);
		if (did_everyone_eat_enough(data) == true)
			return (NULL);
	}
	return (NULL);
}

static bool	did_anyone_died(t_data *data)
{
	int		i;
	long	starving_time;
	long	now;

	i = -1;
	while (++i < data->num_of_philo)
	{
		now = get_time_milisec();
		starving_time = now - data->philo[i].last_meal_time;
		if (starving_time > data->time_to_die)
		{
			pthread_mutex_lock(&data->mutex_death);
			data->someone_died = true;
			pthread_mutex_unlock(&data->mutex_death);
			return (true);
		}
	}
	return (false);
}

static bool	did_everyone_eat_enough(t_data *data)
{
	int	i;
	int	eaten_enough_check;

	if (data->meal_frequency <= 0)
		return (false);
	eaten_enough_check = 0;
	i = -1;
	while (++i < data->num_of_philo)
	{
		pthread_mutex_lock(&data->philo[i].mutex_meal_count);
		if (data->philo[i].total_meal_eaten == data->meal_frequency)
			eaten_enough_check++;
		pthread_mutex_unlock(&data->philo[i].mutex_meal_count);
	}
	if (data->num_of_philo == eaten_enough_check)
	{
		pthread_mutex_lock(&data->philo[i].mutex_meal_count);
		data->all_have_eaten_enough = true;
		pthread_mutex_unlock(&data->philo[i].mutex_meal_count);
		return (true);
	}
	return (false);
}
