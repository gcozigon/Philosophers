/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:23:01 by gcozigon          #+#    #+#             */
/*   Updated: 2023/10/09 03:06:44 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int ac, char **av)
{
	t_all	*all;

	all = starton();
	if (ac == 5 || ac == 6)
		pars_args(av, all);
	else
		return (printf("Error whith arguments\n"), 0);
}

void	free_all_mutex(t_all *all)
{
	pthread_mutex_destroy(&all->die);
	pthread_mutex_destroy(&all->print);
	pthread_mutex_destroy(&all->nbeatlock);
	pthread_mutex_destroy(&all->count_every_eat);
}

int	ft_detatch(t_philo *philo, int num_threads)
{
	int	i;

	i = -1;
	while (++i < num_threads)
		pthread_detach(philo[i].thread);
	return (0);
}
