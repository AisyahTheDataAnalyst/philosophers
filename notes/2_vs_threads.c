/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_vs_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:36:59 by aimokhta          #+#    #+#             */
/*   Updated: 2025/06/24 11:06:38 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int x = 2;

void	*routine()
{
	x++;
	sleep(2);
	printf("Value of x: %d\n", x);
}

void	*routine2()
{
	sleep(2);
	printf("Value of x: %d\n", x);
}

int main(int ac, char **av)
{
	pthread_t	t1;
	pthread_t	t2;

	if (pthread_create(&t1, NULL, &routine, NULL))
		return (1);
	if (pthread_create(&t2, NULL, &routine2, NULL))
		return(2);
	if (pthread_join(t1, NULL))
		return(3);
	if (pthread_join(t2, NULL))
		return(4);
	return(0);
}

//OUTPUT => x:3 && x:3