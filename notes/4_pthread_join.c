/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_pthread_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:37:44 by aimokhta          #+#    #+#             */
/*   Updated: 2025/06/23 17:53:12 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

//x fahammm
void	*roll_dice()
{
	int value = (rand() % 6) + 1;
	int *result = malloc(sizeof(int));
	*result = value;
	// printf("%d\n", value);
	printf("Thread result: %p\n", result);
	return (void*) result;
}

int main(int ac, char **av)
{
	int *res;
	srand(time(NULL));
	pthread_t	th;
	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
		return 1;
	if (pthread_join(th, (void **) &res) != 0)
		return 2;
	printf("Main res: %p\n", res);
	printf("Result: %d\n", *res);
	free(res);
	return (0);
}