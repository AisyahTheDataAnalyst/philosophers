/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_detached_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:53:23 by aimokhta          #+#    #+#             */
/*   Updated: 2025/06/24 09:47:44 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define THREAD_NUM 2

void *routine(void *args)
{
	sleep(1);
	printf("Finished execution\n");
}

int main(int ac, char **av)
{
	pthread_t 	th[THREAD_NUM];
	int			i;

	for (i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			perror("1. Failed to create thread");
		pthread_detach(th[i]);
		printf("%lu\n", th[i]);
	}
	for (i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("2. Failed to join thread");
	}
	// pthread_exit(0);
}