/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:19:36 by aimokhta          #+#    #+#             */
/*   Updated: 2025/08/08 11:00:21 by aimokhta         ###   ########.fr       */
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

# define GREEN "\033[0;32m"
# define LIGHT_CYAN "\033[0;96m"
# define BLUE "\033[0;34m"
# define RED "\033[1;31m"
# define RESET "\033[0m" 

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				total_meal_eaten;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*right_fork; // just a pointer to data->forks
	pthread_mutex_t	*left_fork; /// just a pointer to data->forks
	pthread_mutex_t	mutex_meal;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_frequency;
	bool			someone_died;
	bool			all_have_eaten_enough;
	bool			print_once_only;
	long			start_time;
	t_philo			*philo; // malloced
	pthread_mutex_t	*forks; // malloced, thats why it has *pointer
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	mutex_print;
}	t_data;

//2_parsing.c
int		parsing(int ac, char **av, t_data *data);

//3.1_philo.c
void	*philo_routine(void *arg);

//3.2_philo.c
int		only_one_philo(t_philo *philo, t_data *data);
int		enoughmeal_or_death_check(t_data *data);

//4_monitor.c
void	*monitor_routine(void *arg);

// utils.c
bool	arg_is_valid_digit(char **av);
int		ft_atoi(const char *str);
int		ft_isdigit(int d);
long	get_time_milisec(void);
void	printing_philo(t_philo *philo, long start_time, char *msg);

#endif