/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:46:35 by gcozigon          #+#    #+#             */
/*   Updated: 2023/10/09 00:51:33 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	long	res;
	int		signe;

	i = 0;
	res = 0;
	signe = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			signe = signe * -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = (res * 10) + nptr[i] - '0';
		if ((res * signe) > INT_MAX)
			return (-2);
		i++;
	}
	return (res * signe);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

int	check_die(t_all *all)
{
	int	bool;

	pthread_mutex_lock(&all->die);
	bool = all->dead;
	pthread_mutex_unlock(&all->die);
	return (bool);
}

t_all	*starton(void)
{
	static t_all	all;

	return (&all);
}

void	ft_destroy_mutex(t_philo *philo, t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->nbphilo)
	{
		pthread_mutex_destroy(&philo[i].ceat);
		pthread_mutex_destroy(&philo[i].finish);
		pthread_mutex_destroy(&philo[i].left);
	}
	free_all_mutex(all);
}
