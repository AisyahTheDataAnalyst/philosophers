/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_philo_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:11:41 by aimokhta          #+#    #+#             */
/*   Updated: 2025/08/08 16:58:15 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*philo_routine(void *arg);
static int	philo_eat(t_philo *philo, t_data *data, char *msg);
static int	philo_sleep(t_philo *philo, t_data *data, char *msg);
static int	philo_think(t_philo *philo, t_data *data, char *msg);

// usleep(1000) = 1 milisecond - gives a start to odd philos first - no deadlock
//
// usleep(100) gives CPU time each loop, switch btween philo&monitor
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
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if ((philo->id % 2) == 0)
		usleep(1000);
	while (1)
	{
		if (philo_eat(philo, philo->data, GREEN "is eating" RESET) == 1)
			return (NULL);
		if (philo_sleep(philo, philo->data, "is sleeping") == 1)
			return (NULL);
		if (philo_think(philo, philo->data, "is thinking") == 1)
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

// the sequence of left and right fork is important for 
// edge cases where to avoid deadlock. 
// if 3 philo, philo_1 and philo_3 (odds) go together after usleep(1000):
// - philo_1 take right fork
// - philo_3 take right fork too, but locked by philo_1, will wait after unlock
//
// - if both philo_1 & philo_3 take their own left, they    
static int	philo_eat(t_philo *philo, t_data *data, char *eat_msg)
{
	if (data->num_of_philo == 1)
		return (only_one_philo(philo, data));
	if (enoughmeal_or_death_check(data) == 1)
		return (1);
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
	printing_philo(philo, data->start_time, "has taken a fork");
	printing_philo(philo, data->start_time, "has taken a fork");
	pthread_mutex_lock(&philo->mutex_meal);
	philo->last_meal_time = get_time_milisec();
	philo->total_meal_eaten++;
	printing_philo(philo, data->start_time, eat_msg);
	pthread_mutex_unlock(&philo->mutex_meal);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (enoughmeal_or_death_check(data));
}

static int	philo_sleep(t_philo *philo, t_data *data, char *sleep_msg)
{
	int	time;

	time = 0;
	if (enoughmeal_or_death_check(data) == 0)
	{
		printing_philo(philo, data->start_time, sleep_msg);
		usleep(data->time_to_sleep * 1000);
	}
	return (enoughmeal_or_death_check(data));
}

static int	philo_think(t_philo *philo, t_data *data, char *think_msg)
{
	if (enoughmeal_or_death_check(data) == 0)
		printing_philo(philo, data->start_time, think_msg);
	return (enoughmeal_or_death_check(data));
}
