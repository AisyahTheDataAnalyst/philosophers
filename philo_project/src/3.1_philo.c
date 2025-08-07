/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.1_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:11:41 by aimokhta          #+#    #+#             */
/*   Updated: 2025/08/07 17:37:08 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*philo_routine(void *arg);
static int	philo_eat(t_philo *philo, t_data *data, char *msg);
// static void	philo_lock_print_forks_only(t_philo *philo, t_data *data);
static int	philo_sleep(t_philo *philo, t_data *data, char *msg);
static int	philo_think(t_philo *philo, t_data *data, char *msg);


// usleep(1000) = 1 milisecond
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("Philo %d start time: %ld\n", philo->id, philo->data->start_time);
	if ((philo->id % 2) != 0)
		usleep(1000);
	while (1)
	{
		if (philo_eat(philo, philo->data, GREEN "is eating" RESET) == 1)
			return (NULL);
		if (philo_sleep(philo, philo->data, "is sleeping") == 1)
			return (NULL);
		if (philo_think(philo, philo->data, "is thinking") == 1)
			return (NULL);
		// if ((philo->id % 2) == 0)
		usleep(100);
	}
	return (NULL);
}

// lock right and left fork within eating lock
static int	philo_eat(t_philo *philo, t_data *data, char *eat_msg)
{
	int	time;

	time = 0;
	if (data->num_of_philo == 1)
		return(only_one_philo(philo, data));
	//
	if (enoughmeal_or_death_check(data) == 1)
		return (1);
	// philo_lock_print_forks_only(philo, data);
	// pthread_mutex_lock(&data->mutex_print);
	if ((philo->id % 2) == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}

	// pthread_mutex_lock(philo->right_fork);
	printing_philo(philo, data->start_time, "has taken a fork");

	// pthread_mutex_lock(philo->left_fork);
	printing_philo(philo, data->start_time, "has taken a fork");

	printing_philo(philo, data->start_time, eat_msg);

	// while (++time <= data->time_to_eat)
	// 	usleep(1000);
	pthread_mutex_lock(&philo->mutex_meal_count);
	philo->last_meal_time = get_time_milisec();
	usleep(data->time_to_eat * 1000);
	philo->total_meal_eaten++;
	pthread_mutex_unlock(&philo->mutex_meal_count);

	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);

	// pthread_mutex_unlock(&data->mutex_print);
	
	return (enoughmeal_or_death_check(data));
}

// static void	philo_lock_print_forks_only(t_philo *philo, t_data *data)
// {
	
// }

static int	philo_sleep(t_philo *philo, t_data *data, char *sleep_msg)
{
	int	time;

	time = 0;
	if (enoughmeal_or_death_check(data) == 0)
	{
		// pthread_mutex_lock(&data->mutex_print);
		printing_philo(philo, data->start_time, sleep_msg);
		// while (++time <= data->time_to_sleep)
		// 	usleep(1000);
		usleep(data->time_to_sleep * 1000);
		// pthread_mutex_unlock(&data->mutex_print);
	}
	return (enoughmeal_or_death_check(data));
}

static int	philo_think(t_philo *philo, t_data *data, char *think_msg)
{
	if (enoughmeal_or_death_check(data) == 0)
	{
		// pthread_mutex_lock(&data->mutex_print);
		printing_philo(philo, data->start_time, think_msg);
		// pthread_mutex_unlock(&data->mutex_print);
	}
	return (enoughmeal_or_death_check(data));
}
