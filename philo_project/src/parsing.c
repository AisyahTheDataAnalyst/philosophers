/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:12:20 by aimokhta          #+#    #+#             */
/*   Updated: 2025/07/02 10:23:41 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			parsing(int ac, char **av, t_data *data);
static int	parsing_arg(int ac, char **av, t_arg arg);
static int	parsing_philo(t_philo **philo, t_arg arg);
static int	parsing_data(t_data *data);

int	parsing(int ac, char **av, t_data *data)
{
	if (parsing_arg(ac, av, data->arg) == 1)
		return (1);
	if (parsing_philo(&data->philo, data->arg) == 1)
		return (1);
	if (parsing_data(data) == 1)
		return (1);
	return (0);
}

static int	parsing_arg(int ac, char **av, t_arg arg)
{
	if (ac == 5 || ac == 6)
	{
		arg.num_of_philo = ft_atoi(av[1]);
		arg.time_to_die = ft_atol(av[2]);
		arg.time_to_eat = ft_atol(av[3]);
		arg.time_to_sleep = ft_atol(av[4]);
		if (ac == 6 && ft_atoi(av[5]) > 0)
			arg.times_each_philo_must_eat = ft_atoi(av[5]);
		else
			arg.times_each_philo_must_eat = 0;
	}
	if (arg.num_of_philo == 0 || arg.time_to_die == 0 || arg.time_to_eat == 0
		|| arg.time_to_sleep == 0)
		return (1);
	return (0);
}

static int	parsing_philo(t_philo **philo, t_arg arg)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo));
	if (!*philo)
		return (1);
	while (i < arg.num_of_philo)
	{
		philo[i]->thread = malloc(sizeof(pthread_t));
		if (!philo[i]->thread)
			return (1);
		philo[i]->id = i + 1;
		philo[i]->last_meal_time = get_time_milisec();
		i++;
	}
	return (0);
}

static int	parsing_data(t_data *data)
{
	data->start_time = get_time_milisec();
	data->simulation_end = false;
	data->forks = data->arg.num_of_philo;
	return (0);
}







