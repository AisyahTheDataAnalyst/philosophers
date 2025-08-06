/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:12:20 by aimokhta          #+#    #+#             */
/*   Updated: 2025/08/06 10:00:21 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			parsing(int ac, char **av, t_data *data);
static int	parsing_arguments(int ac, char **av, t_data *data);
static int	parsing_malloc(t_data *data);
static int	parsing_struct_members(t_philo *philo, t_data *data);

int	parsing(int ac, char **av, t_data *data)
{
	if (parsing_arguments(ac, av, data) == 1)
		return (ft_putendl_fd("Invalid arguments", 2), 1);
	if (parsing_malloc(data) == 1)
		return (ft_putendl_fd("Malloc failed", 2) , 1);
	if (parsing_struct_members(data->philo, data) == 1)
		return (ft_putendl_fd("Initializing mutex failed", 2), 1);
	return (0);
}

static int	parsing_arguments(int ac, char **av, t_data *data)
{
	if ((ac == 5 || ac == 6) && arg_is_valid_digit(av) == true)
	{
		data->num_of_philo = ft_atoi(av[1]);
		data->time_to_die = ft_atoi(av[2]);
		data->time_to_eat = ft_atoi(av[3]);
		data->time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			data->total_meal_frequency = ft_atoi(av[5]);
		else
			data->total_meal_frequency = 0;
	}
	if (data->num_of_philo == 0 || data->time_to_die == 0 || \
data->time_to_eat == 0 || data->time_to_sleep == 0)
		return (1);
	fprintf(stderr, "1st parse\n");
	return (0);
}

static int	parsing_malloc(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!data->philo)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (!data->forks)
		return (1);
	fprintf(stderr, "2nd parse\n");
	return (0);
}

static int	parsing_struct_members(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].last_meal_time = get_time_milisec();
		fprintf(stderr, "philo[%d] last meal time = %d\n", i, philo[i].last_meal_time);
		philo[i].right_fork = &data->forks[i];
		philo[i].left_fork = &data->forks[(i + 1) % data->num_of_philo];
		if (pthread_mutex_init(&philo[i].meal_count, NULL) != 0)
			return (1);
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		fprintf(stderr, "after each philo's mutex init\n");
	}
	if (pthread_mutex_init(&data->mutex_death, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->mutex_print, NULL) != 0)
		return (1);
	data->start_time = get_time_milisec();
	data->someone_died = false;
	fprintf(stderr, "3rd parse\n");
	return (0);
}
