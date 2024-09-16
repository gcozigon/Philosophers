/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:41:34 by gcozigon          #+#    #+#             */
/*   Updated: 2023/10/09 05:13:32 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long int	get_time(void)
{
	struct timeval	time;
	int				tmp;

	tmp = gettimeofday(&time, NULL);
	if (tmp == -1)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	do_usleep(long int duration)
{
	long	begin;

	begin = get_time();
	while (get_time() - begin < duration)
		usleep(10);
	return (1);
}

int	print_msg(t_philo *philo, char *msg)
{
	t_all	*all;

	all = starton();
	pthread_mutex_lock(&all->print);
	if (!check_die(all))
	{
		pthread_mutex_unlock(&all->print);
		return (1);
	}
	printf("%lld %d %s", get_time() - philo->time, philo->name + 1, msg);
	pthread_mutex_unlock(&all->print);
	return (0);
}

int	every_philo_eat(t_philo *philo, t_all *all)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < all->nbphilo)
	{
		pthread_mutex_lock(&philo[i].ceat);
		if (philo[i].nb_eat == 0)
		{
			pthread_mutex_lock(&all->count_every_eat);
			count++;
			pthread_mutex_unlock(&all->count_every_eat);
		}
		pthread_mutex_unlock(&philo[i].ceat);
	}
	if (count == all->nbphilo)
		return (1);
	return (0);
}

void	ft_dead(t_all *all, int i, t_philo *philo)
{
	pthread_mutex_lock(&all->die);
	all->dead = 0;
	pthread_mutex_unlock(&all->die);
	pthread_mutex_lock(&all->print);
	printf("%lld %d died	\n", (get_time() - philo[i].time), philo->name + 1);
	pthread_mutex_unlock(&all->print);
}
