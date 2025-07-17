/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_process_vs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:37:47 by aimokhta          #+#    #+#             */
/*   Updated: 2025/06/24 11:05:32 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int ac, char **av)
{
	int	x = 2;
	int	pid = fork();
	if (pid == -1)
		return 1;
	if (pid == 0)
		x++;
	sleep(2);
	printf("Value of x: %d\n", x);
	// printf("Process id %d\n", getpid());
	if (pid != 0)
		wait(NULL);
	
}

// OUTPUT => x : 2 && x : 3