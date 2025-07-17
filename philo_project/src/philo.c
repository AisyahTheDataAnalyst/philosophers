/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:19:33 by aimokhta          #+#    #+#             */
/*   Updated: 2025/07/01 11:15:06 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data->philo = init(ac, av, data->philo);
	if (!data->philo || data->philo->num_of_philo >= 0
		|| data->philo->time_to_die >= 0 || data->philo->time_to_eat >= 0
		|| data->philo->time_to_sleep >= 0)
	{
		printf("Argument error\n");
		return (1);
	}
	start_stimulation(data);
	freeing(data);
	return (0);
}

void	start_simulation(t_data *data)
{
	// pthread_t		th[data->philo->num_of_philo];
	int				i;
	// long			start_time;
	// long			timestamp;

	start_time = get_time_milisec();

	pthread_mutex_init(data->mutex, NULL);
	i = -1;
	while (++i < data->philo->num_of_philo)
		if (pthread_create(&th[i], NULL, NULL, NULL))
			perror("pthread_create");

	while (1)
	{
		i = 0;
		while (++i <= data->philo->num_of_philo)
		{
			timestamp = eating(data, start_time);
			if (timestamp > data->philo->time_to_eat)
				
			else	
				printf("%d %d is eating\n", timestamp, i);
				if (++i <= data->philo->num_of_philo)
				{
					timestamp = sleeping(data, start_time);
					printf("%d %d is sleeping\n", timestamp, i);
				}
		}
	}

	i = -1;
	while (++i < data->philo->num_of_philo)
		if (pthread_join(th[i], NULL))
			perror("pthread_join");
	pthread_mutex_destroy(data->mutex);
}

long	eating(t_data *data, long start_time)
{
	long	current_time;
	long	timestamp;

	current_time = get_time_milisec();
	pthread_mutex_lock(data->mutex);
	usleep(data->philo->time_to_eat * 1000);
	pthread_mutex_unlock(data->mutex);
	timestamp = current_time - start_time;
	return (timestamp);
}

long	sleeping(t_data *data, long start_time)
{
	long	current_time;
	long	timestamp;

	current_time = get_time_milisec();
	pthread_mutex_lock(data->mutex);
	usleep(data->philo->time_to_sleep * 1000);
	pthread_mutex_unlock(data->mutex);
	timestamp = current_time - start_time;
	return (timestamp);
}

// usleep 
// gettimeofday
// implement this by yoiurself

// fn that monitor the philo, finish die or finish or inifity __LONG_LONG_PAIR

// performance, run on terminal original

// understand data race this is what its about to solve the data race problme medium article

// usleep ( x * 1000) => 0.001second = 1 milisecond

// 2 struct , philo and table