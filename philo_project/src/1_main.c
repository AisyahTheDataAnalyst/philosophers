/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:47:26 by aimokhta          #+#    #+#             */
/*   Updated: 2025/08/06 10:07:03 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	freeing(t_data *data);

int	main(int ac, char **av)
{
	t_data	data;

	if (parsing(ac, av, &data) == 1)
		return (1);
	// if (start_simulation(&data) == 1)
	// {
	// 	freeing(&data);
	// 	return (1);
	// }
	freeing(&data);
	return (0);
}

// static int	start_simulation(t_data *data)
// {
// 	if (create_philo(data, &data->philo) == 1)
// 		return (1);
// 	if (pthread_create(data, NULL, &monitor_routine, NULL) == 1)
// 		return (1);
// 	if (join_philo(&data->philo) == 1)
// 		return (1);
// 	if (pthread_join(data, NULL) == 1)
// 		return (1);
// }

static void	freeing(t_data *data)
{
	int	i;

	if (data->philo)
	{

		i = 0;
		while (i < data->num_of_philo)
		{
			pthread_mutex_destroy(&data->philo[i].meal_count);
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		fprintf(stderr, "freeing malloced\n");
		free(data->philo);
		free(data->forks);
	}
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_death);
	fprintf(stderr, "freed malloc and destroy mutex\n");
}
