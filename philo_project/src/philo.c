/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:47:26 by aimokhta          #+#    #+#             */
/*   Updated: 2025/07/01 16:53:55 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (parsing(ac, av, &data) == 1)
		return (1);
	start_simulation(&data);
	// freeing(&data);
	return (0);
}

