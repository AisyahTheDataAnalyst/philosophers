/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:30:39 by aimokhta          #+#    #+#             */
/*   Updated: 2025/08/08 17:50:44 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	arg_is_valid_digit(char **av)
{
	int	i;
	int	j;

	if (!av || !av[0])
		return (false);
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]))
				j++;
			else
				return (false);
		}
		i++;
	}
	return (true);
}

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

int	ft_isdigit(int d)
{
	if (d >= '0' && d <= '9')
		return (1);
	return (0);
}

//turning the time into miliseconds
long	get_time_milisec(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((long)(now.tv_sec * 1000) + (now.tv_usec / 1000));
}

void	printing_philo(t_philo *philo, long start_time, char *msg)
{
	long	current_time;

	pthread_mutex_lock(&philo->data->mutex_death);
	pthread_mutex_lock(&philo->data->mutex_print);
	if (!philo->data->someone_died && !philo->data->all_have_eaten_enough)
	{
		current_time = get_time_milisec() - start_time;
		printf("%ld %d %s\n", current_time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->mutex_print);
	pthread_mutex_unlock(&philo->data->mutex_death);
}
