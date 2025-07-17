/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:30:39 by aimokhta          #+#    #+#             */
/*   Updated: 2025/06/26 15:49:02 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(result * sign));
}

t_milisecond	ft_atol(const char *str)
{
	int				i;
	t_milisecond	sign;
	t_milisecond	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return ((result * sign));
}

//turning the time into miliseconds
t_milisecond	get_time_milisec(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((t_milisecond)(now.tv_sec * 1000) + (now.tv_usec / 1000));
}

void	printing(char *str)
{
	t_milisecond 	curr_time;
	t_data 			*data;
	
	curr_time = data->philo->last_meal_time - data->start_time;
	printf("%ld %d %s", curr_time, data->philo->id, str);
}