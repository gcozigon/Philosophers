/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:04:25 by gcozigon          #+#    #+#             */
/*   Updated: 2023/10/09 05:14:26 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	valid_integer(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (!((j == 0 && av[i][j] == '+' && av[i][j + 1] >= '0' && av[i][j
				+ 1] <= '9') || (av[i][j] >= '0' && av[i][j] <= '9')))
				return (1);
		}
		i++;
	}
	return (0);
}

int	init_all(char **av, t_all *all)
{
	pthread_mutex_init(&all->print, NULL);
	pthread_mutex_init(&all->die, NULL);
	pthread_mutex_init(&all->nbeatlock, NULL);
	pthread_mutex_init(&all->count_every_eat, NULL);
	all->dead = 1;
	all->timestart = get_time();
	all->nbphilo = ft_atoi(av[1]);
	all->time_to_die = ft_atoi(av[2]);
	all->time_to_eat = ft_atoi(av[3]);
	all->ttsleep = ft_atoi(av[4]);
	if (av[5])
		all->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		all->number_of_times_each_philosopher_must_eat = -1;
	if (all->timestart == -2 || all->nbphilo == -2 || all->time_to_die == -2
		|| all->time_to_eat == -2 || all->ttsleep == -2
		|| all->number_of_times_each_philosopher_must_eat == -2)
		return (0);
	return (1);
}

void	init_philo(t_philo *philo, t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->nbphilo - 1)
		philo[i].right = &philo[i + 1].left;
	philo[i].right = &philo[0].left;
	i = -1;
	while (++i < all->nbphilo)
	{
		philo[i].finisheat = 0;
		philo[i].name = i;
		philo[i].time = get_time();
		philo[i].nb_eat = all->number_of_times_each_philosopher_must_eat;
	}
	i = -1;
	while (++i < all->nbphilo)
	{
		pthread_mutex_init(&philo[i].finish, NULL);
		pthread_mutex_init(&philo[i].left, NULL);
		pthread_mutex_init(&philo[i].ceat, NULL);
	}
}

void	check_dead_philo(t_philo *philo, t_all *all)
{
	int			i;
	long long	fulltime;

	while (1)
	{
		i = -1;
		while (++i < all->nbphilo)
		{
			pthread_mutex_lock(&philo[i].finish);
			fulltime = get_time() - all->timestart - philo[i].finisheat;
			pthread_mutex_unlock(&philo[i].finish);
			if (fulltime >= all->time_to_die)
				return (ft_dead(all, i, philo));
			if (every_philo_eat(philo, all) == 1)
			{
				pthread_mutex_lock(&all->die);
				all->dead = 0;
				pthread_mutex_unlock(&all->die);
			}
		}
		usleep(500);
	}
}

int	pars_args(char **av, t_all *all)
{
	t_philo	*philo;
	int		i;

	if (ft_atoi(av[1]) <= 0)
		return (printf("Error : invalid nb of philo\n"), 0);
	if (valid_integer(av))
		return (printf("Error : invalid ascii\n"), 0);
	if (!(init_all(av, all)))
		return (printf("Error : invalid number\n"), 0);
	philo = malloc(sizeof(t_philo) * all->nbphilo);
	if (!philo)
		return (free_all_mutex(all), 0);
	init_philo(philo, all);
	i = -1;
	while (++i < all->nbphilo)
		if (pthread_create(&philo[i].create, NULL, &ft_routine, &philo[i]))
			return (ft_detatch(philo, i), ft_destroy_mutex(philo, all),
				free(philo), 0);
	check_dead_philo(philo, all);
	i = -1;
	while (++i < all->nbphilo)
		pthread_join(philo[i].create, NULL);
	ft_destroy_mutex(philo, all);
	return (free(philo), 0);
}
