/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:30:16 by aimokhta          #+#    #+#             */
/*   Updated: 2025/06/20 14:32:50 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void	*routine()
{
	printf("Test from threads\n");
	sleep(3);
	printf("Ending thread\n");
}

//gcc -g -pthread 
// new data type = pthread_t
// pthread_create(pointer to the pthread_t, attribute, actual function pointer, argument)
int	main(int ac, char **av)
{
	pthread_t	t1;
	pthread_t	t2;

	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return 1;
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return 2;
	if (pthread_join(t1, NULL) != 0)
		return 3;
	if (pthread_join(t2, NULL) != 0)
		return 4;
	return 0;
}

// pthread_create -> create threads
// pthread_join   -> basically wait() for threads