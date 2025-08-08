/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_philo_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:25:22 by aimokhta          #+#    #+#             */
/*   Updated: 2025/08/08 11:32:37 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	only_one_philo(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(philo->right_fork);
	printing_philo(philo, data->start_time, "has taken a fork");
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&data->mutex_death);
	data->someone_died = true;
	pthread_mutex_unlock(&data->mutex_death);
	return (enoughmeal_or_death_check(data));
}

int	enoughmeal_or_death_check(t_data *data)
{
	// long	current_time;
	
	pthread_mutex_lock(&data->mutex_print);
	if (data->someone_died == true || data->all_have_eaten_enough == true)
	{
		if (data->print_once_only == false)
		{
			if (data->someone_died == true)
			{
				// pthread_mutex_lock(&data->mutex_death);
				// // printing_philo(data->philo, data->start_time, RED "died" RESET);
				// current_time = get_time_milisec() - data->start_time;
				// // pthread_mutex_lock(&data->mutex_print);
				// printf("%ld %d %s\n", current_time, data->philo->id, RED "died" RESET);
				// // pthread_mutex_unlock(&data->mutex_print);
				// pthread_mutex_unlock(&data->mutex_death);
				data->print_once_only = true;
			}
			else
			{
				// pthread_mutex_lock(&data->mutex_print);
				printf("\033[0;96mAll philosophers have eaten enough\033[0m\n");
				data->print_once_only = true;
				// pthread_mutex_unlock(&data->mutex_print);
			}
		}
		pthread_mutex_unlock(&data->mutex_print);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex_print);
	return (0);
}
