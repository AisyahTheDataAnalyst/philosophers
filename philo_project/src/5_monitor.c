/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_monitor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:13:39 by aimokhta          #+#    #+#             */
/*   Updated: 2025/08/08 11:31:41 by aimokhta         ###   ########.fr       */
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
	// usleep(2000);
	while (1)
	{
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
	long	last_meal;
	long	now;
	long	current_time;

	i = -1;
	// pthread_mutex_lock(&data->mutex_death);
	while (++i < data->num_of_philo)
	{
		now = get_time_milisec();
		pthread_mutex_lock(&data->philo[i].mutex_meal);
		// starving_time = now - data->philo[i].last_meal_time;
		last_meal = data->philo[i].last_meal_time;
		pthread_mutex_unlock(&data->philo[i].mutex_meal);
		if (now - last_meal >= data->time_to_die)
		{
			pthread_mutex_lock(&data->mutex_death);
			pthread_mutex_lock(&data->mutex_print);
			current_time = get_time_milisec() - data->start_time;
			printf("%ld %d %s\n", current_time, data->philo->id, RED "died" RESET);
			data->someone_died = true;
			pthread_mutex_unlock(&data->mutex_print);
			pthread_mutex_unlock(&data->mutex_death);
			return (true);
		}
	}
	// pthread_mutex_unlock(&data->mutex_death);
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
		pthread_mutex_lock(&data->philo[i].mutex_meal);
		if (data->philo[i].total_meal_eaten >= data->meal_frequency)
			eaten_enough_check++;
		pthread_mutex_unlock(&data->philo[i].mutex_meal);
	}
	if (data->num_of_philo == eaten_enough_check) // new mutex? no need. change mutex to meal count? no, thtas for each philo[i]. 
		return (data->all_have_eaten_enough = true, true);
	return (false);
}
