/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.2_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:25:22 by aimokhta          #+#    #+#             */
/*   Updated: 2025/08/07 18:22:50 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	only_one_philo(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(philo->right_fork);
	printing_philo(philo, data->start_time, "has taken a fork");
	while (data->someone_died == false)
		usleep(100);
	pthread_mutex_unlock(philo->right_fork);
	return (enoughmeal_or_death_check(data));
}

// int	enoughmeal_or_death_check(t_data *data)
// {
// 	pthread_mutex_lock(&data->mutex_print);
// 	if (data->someone_died == true)
// 	{
// 		if (data->print_once_only == false)
// 		{
// 			pthread_mutex_lock(&data->mutex_death);
// 			printing_philo(data->philo, data->start_time, RED "died" RESET);
// 			data->print_once_only = true;
// 			pthread_mutex_unlock(&data->mutex_death);
// 			return (pthread_mutex_unlock(&data->mutex_print), 1);
// 		}
// 	}
// 	pthread_mutex_unlock(&data->mutex_print);
// 	pthread_mutex_lock(&data->mutex_print);
// 	if (data->all_have_eaten_enough == true)
// 	{
// 		if (data->print_once_only == false)
// 		{
// 			printf(LIGHT_CYAN "All philosophers have eaten enough\n" RESET);
// 			data->print_once_only = true;
// 			return (pthread_mutex_unlock(&data->mutex_print), 1);
// 		}
// 	}
// 	pthread_mutex_unlock(&data->mutex_print);
// 	return (0);
// }

int	enoughmeal_or_death_check(t_data *data)
{
	pthread_mutex_lock(&data->mutex_print);
	if (data->someone_died == true || data->all_have_eaten_enough == true)
	{
		if (data->print_once_only == false) // remove later
		{
			if (data->someone_died == true)
			{
				pthread_mutex_lock(&data->mutex_death);
				printing_philo(data->philo, data->start_time, RED "died" RESET);
				pthread_mutex_unlock(&data->mutex_death);
			}
			else
				printf(LIGHT_CYAN "All philosophers have eaten enough\n" RESET);
			data->print_once_only = true;
		}
		pthread_mutex_unlock(&data->mutex_print);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex_print);
	return (0);
}
