/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:19:36 by aimokhta          #+#    #+#             */
/*   Updated: 2025/07/01 14:32:50 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h> 
# include <string.h>

typedef long	t_milisecond;

typedef struct s_arg
{
	int				num_of_philo;
	t_milisecond	time_to_die;
	t_milisecond	time_to_eat;
	t_milisecond	time_to_sleep;
	int				times_each_philo_must_eat;
}	t_arg;

typedef struct s_philo
{
	pthread_t		*thread;
	int				id;
	t_milisecond	last_meal_time;
	pthread_mutex_t	*mutex_meal;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	// struct			s_data;
}	t_philo;

typedef struct s_data
{
	t_arg			arg;
	t_philo			*philo;
	pthread_mutex_t	*mutex_death;
	pthread_mutex_t	*mutex_print;
	t_milisecond	start_time;
	bool			simulation_end;
	int				forks;
}	t_data;



//parsing.c
int				parsing(int ac, char **av, t_data *data);

// utils.c
int				ft_atoi(const char *str);
t_milisecond	ft_atol(const char *str);
t_milisecond	get_time_milisec(void);

#endif