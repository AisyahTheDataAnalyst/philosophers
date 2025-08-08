/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_philo_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:25:22 by aimokhta          #+#    #+#             */
/*   Updated: 2025/08/08 17:17:59 by aimokhta         ###   ########.fr       */
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
	return (1);
}

int	enoughmeal_or_death_check(t_data *data)
{
	pthread_mutex_lock(&data->mutex_death);
	pthread_mutex_lock(&data->mutex_print);
	if (data->someone_died == true || data->all_have_eaten_enough == true)
	{
		pthread_mutex_unlock(&data->mutex_death);
		pthread_mutex_unlock(&data->mutex_print);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex_death);
	pthread_mutex_unlock(&data->mutex_print);
	return (0);
}
