/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_race_conditions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:15:56 by aimokhta          #+#    #+#             */
/*   Updated: 2025/06/24 14:55:34 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void	*routine()
{
	for (int i = 0; i < 10000000; i++)
	{
			// if (lock == 1)
			//		wait to make it lock = 0;
			//	lock = 1;
		pthread_mutex_lock(&mutex);
		mails++;
			//	lock = 0;
		pthread_mutex_unlock(&mutex);
		//read
		//increment
		//write
	}
}

//this way all threads goes in parallel
//the printf results dosent mean they ended in order, its just how the printf works in for loop
int main(int ac, char **av)
{
	pthread_t	th[8];
	int			i;

	pthread_mutex_init(&mutex, NULL);
	for (i = 0; i < 8; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
			perror("Failed to create thread");
			return 1;
		}
		printf("Thread %d has started\n", i);
	}
	for (i = 0; i < 8; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
			return 3;
		printf("Thread %d has finished executed\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails); // will be 2K
	return 0;
}

//&th[i] == th + i
//this is wrong because technically you just gonna have 1 thread executed at a time 
// int main(int ac, char **av)
// {
// 	pthread_t	th[4];
// 	int			i;

// 	pthread_mutex_init(&mutex, NULL);
// 	for (i = 0; i < 4; i++)
// 	{
// 		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
// 		{
// 			perror("Failed to create thread");
// 			return 1;
// 		}
// 		printf("Thread %d has started\n", i);
// 		if (pthread_join(th[i], NULL) != 0)
// 			return 3;
// 		printf("Thread %d has finished executed\n", i);
// 	}
// 	pthread_mutex_destroy(&mutex);
// 	printf("Number of mails: %d\n", mails); // will be 2K
// 	return 0;
// }



// int main(int ac, char **av)
// {
// 	pthread_t		t1;
// 	pthread_t		t2;
// 	pthread_t		t3;
// 	pthread_t		t4;

// 	pthread_mutex_init(&mutex, NULL);
// 	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
// 		return 1;
// 	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
// 		return 2;
// 	if (pthread_create(&t3, NULL, &routine, NULL) != 0)
// 		return 1;
// 	if (pthread_create(&t4, NULL, &routine, NULL) != 0)
// 		return 2;
// 	if (pthread_join(t1, NULL) != 0)
// 		return 3;
// 	if (pthread_join(t2, NULL) != 0)
// 		return 4;
// 	if (pthread_join(t3, NULL) != 0)
// 		return 3;
// 	if (pthread_join(t4, NULL) != 0)
// 		return 4;
// 	pthread_mutex_destroy(&mutex);
// 	printf("Number of mails: %d\n", mails); // will be 2K
// 	return 0;
// }