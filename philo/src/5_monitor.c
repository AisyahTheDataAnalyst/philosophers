/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_monitor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:13:39 by aimokhta          #+#    #+#             */
/*   Updated: 2025/08/08 16:29:01 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*monitor_routine(void *arg);
static bool	did_anyone_died(t_data *data);
static bool	did_everyone_eat_enough(t_data *data);

// // usleep(100) gives CPU time each loop, switch btween philo&monitor
// ----------
// with :
// Time(ms):  0   0.1   0.2   0.3   0.4   0.5 ...
// CPU:      P1   M     P2    M     P3    M   ...  (monitor runs between philos)
// ----------
// without :
// Time(ms):  0   1   2   3   4   5   6   7 ...
// CPU:      P1  P2  P3  P4  P5  P1  P2  P3  ...  (monitor delayed)
// ----------
// important for tight time like ./philo 5 800 200 200
void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (did_anyone_died(data) == true)
			return (NULL);
		if (did_everyone_eat_enough(data) == true)
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

static bool	did_anyone_died(t_data *data)
{
	int		i;
	long	last_meal;
	long	now;

	i = -1;
	while (++i < data->num_of_philo)
	{
		now = get_time_milisec();
		pthread_mutex_lock(&data->philo[i].mutex_meal);
		last_meal = data->philo[i].last_meal_time;
		pthread_mutex_unlock(&data->philo[i].mutex_meal);
		if (now - last_meal >= data->time_to_die)
		{
			pthread_mutex_lock(&data->mutex_death);
			pthread_mutex_lock(&data->mutex_print);
			printf("%ld %d %s\n", get_time_milisec() - data->start_time,
				data->philo->id, RED "died" RESET);
			data->someone_died = true;
			pthread_mutex_unlock(&data->mutex_print);
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
		pthread_mutex_lock(&data->philo[i].mutex_meal);
		if (data->philo[i].total_meal_eaten >= data->meal_frequency)
			eaten_enough_check++;
		pthread_mutex_unlock(&data->philo[i].mutex_meal);
	}
	if (data->num_of_philo == eaten_enough_check)
	{
		pthread_mutex_lock(&data->mutex_print);
		printf("\033[0;96mAll philosophers have eaten at least ");
		printf("%d times\033[0m\n", data->meal_frequency);
		data->all_have_eaten_enough = true;
		pthread_mutex_unlock(&data->mutex_print);
		return (true);
	}
	return (false);
}
