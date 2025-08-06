/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:19:36 by aimokhta          #+#    #+#             */
/*   Updated: 2025/08/06 09:45:46 by aimokhta         ###   ########.fr       */
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

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				last_meal_time;
	pthread_t		*thread;
	pthread_mutex_t	*right_fork; // just a pointer to data->forks
	pthread_mutex_t	*left_fork; /// just a pointer to data->forks
	pthread_mutex_t	meal_count;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				total_meal_frequency;
	int				start_time;
	bool			someone_died;
	t_philo			*philo; // malloced
	pthread_mutex_t	*forks; // malloced, thats why it has *pointer
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	mutex_print;
}	t_data;

// main.c
// int		start_simulation(t_data *data);

//parsing.c
int		parsing(int ac, char **av, t_data *data);

// utils.c
bool	arg_is_valid_digit(char **av);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_isdigit(int d);
int		get_time_milisec(void);

#endif