/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:26:04 by gcozigon          #+#    #+#             */
/*   Updated: 2023/10/09 04:38:56 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_all	t_all;

// #define malloc(x) NULL

typedef struct s_philo
{
	long long			time;
	int					name;
	int					nb_eat;
	long long			finisheat;
	pthread_mutex_t		left;
	pthread_mutex_t		finish;
	pthread_mutex_t		*right;
	pthread_mutex_t		ceat;
	pthread_t			create;
	pthread_t			thread;
	t_all				*all;
}						t_philo;

typedef struct s_all
{
	int					nbphilo;
	int					time_to_die;
	int					time_to_eat;
	int					ttsleep;
	int					number_of_times_each_philosopher_must_eat;
	int					dead;
	int					finish;
	long long			timestart;
	pthread_mutex_t		*fork;
	pthread_mutex_t		count_every_eat;
	pthread_mutex_t		print;
	pthread_mutex_t		die;
	pthread_mutex_t		nbeatlock;
	t_philo				*philo;
}						t_all;

int						pars_args(char **av, t_all *all);
int						ft_atoi(const char *nptr);
long int				get_time(void);
void					*ft_routine(void *arg);
void					*ft_memset(void *s, int c, size_t n);
int						do_usleep(long int duration);
int						print_msg(t_philo *philo, char *msg);
t_all					*starton(void);
int						check_die(t_all *all);
void					ft_destroy_mutex(t_philo *philo, t_all *all);
void					ft_dead(t_all *all, int i, t_philo *philo);
int						every_philo_eat(t_philo *philo, t_all *all);
void					ft_destroy_mutex(t_philo *philo, t_all *all);
void					free_all_mutex(t_all *all);
int						ft_detatch(t_philo *philo, int num_threads);

#endif
