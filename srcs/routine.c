/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:51:34 by gcozigon          #+#    #+#             */
/*   Updated: 2023/10/09 04:50:47 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	take_fork(t_philo *philo)
{
	if (philo->name % 2)
	{
		pthread_mutex_lock(&philo->left);
		print_msg(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->right);
		print_msg(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->right);
		print_msg(philo, "has taken a fork\n");
		pthread_mutex_lock(&philo->left);
		print_msg(philo, "has taken a fork\n");
	}
}

int	ft_eat(t_philo *philo, t_all *all)
{
	if (!check_die(all) || philo->nb_eat == 0)
		return (0);
	pthread_mutex_lock(&philo->finish);
	philo->finisheat = get_time() - philo->time;
	pthread_mutex_unlock(&philo->finish);
	pthread_mutex_lock(&philo->ceat);
	if (philo->nb_eat > 0)
		philo->nb_eat--;
	pthread_mutex_unlock(&philo->ceat);
	print_msg(philo, "is eating\n");
	do_usleep(all->time_to_eat);
	return (1);
}

int	ft_sleep_and_think(t_philo *philo, t_all *all)
{
	if (!check_die(all))
		return (0);
	print_msg(philo, "is sleeping\n");
	do_usleep(all->ttsleep);
	print_msg(philo, "is thinking\n");
	if (all->nbphilo % 2)
	{
		if (all->time_to_eat >= all->ttsleep)
			usleep((all->time_to_eat - all->ttsleep) * 1000);
		usleep(500);
	}
	return (1);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	t_all	*all;

	all = starton();
	philo = (t_philo *)arg;
	if (all->nbphilo == 1)
	{
		print_msg(philo, "has taken a fork\n");
		do_usleep(all->time_to_die);
		return (NULL);
	}
	if (philo->name % 2)
		usleep(all->time_to_eat * 500);
	while (check_die(all))
	{
		take_fork(philo);
		ft_eat(philo, all);
		pthread_mutex_unlock(&philo->left);
		pthread_mutex_unlock(philo->right);
		ft_sleep_and_think(philo, all);
	}
	return (NULL);
}
