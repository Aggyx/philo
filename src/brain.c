/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:01:29 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/14 05:52:40 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/lib.h"

static int	takeforks(t_philos *philo)
{
	if (pthread_mutex_lock(philo->lefork))
	{
		printf("ID: %d  - Error at taking left fork\n", philo->id);
		return (1);
	}
	timenow(&philo->ts2);
	printf("%lld %d has taken a fork\n", elapsedtime(&philo->tinit), philo->id);
	if (pthread_mutex_lock(philo->rifork))
	{
		pthread_mutex_unlock(philo->rifork);
		printf("Error at taking right fork\n");
		return (1);
	}
	if (gettimeofday(&philo->ts2, NULL))
		return (1);
	printf("%lld %d has taken a fork\n", elapsedtime(&philo->tinit), philo->id);
	philo->lfk = 1;
	philo->rfk = 1;
	return (0);
}

static int	eat(t_philos *philo)
{
	printf("%lld %d is eating\n", elapsedtime(&philo->tinit), philo->id);
	usleep(philo->time_eat * 1000);
	philo->lfk = 0;
	philo->rfk = 0;
	if (pthread_mutex_unlock(philo->lefork))
		return (1);
	if (pthread_mutex_unlock(philo->rifork))
		return (1);
	philo->thinkflag = 1;
	printf("%lld %d is sleeping\n", elapsedtime(&philo->tinit), philo->id);
	return (0);
}

void	*routine(void *philp)
{
	t_philos	*philo;

	philo = (t_philos *)philp;
	if (gettimeofday(&philo->ts, NULL))
		return ((void *)1);
	if (philo->id % 2 == 0)
		usleep(50);
	while (!philo->dead)
	{
		if (takeforks(philo))
		{
			diestarvation(philo);
			continue ;
		}
		eat(philo);
		if (elapsedtime(&philo->ts2) >= philo->time_die + 10)
		{
			printf("TIME");
			break ;
		}
		usleep(philo->time_slp);
		diestarvation(philo);
		philo->iter++;
	}
	return ((void *)0);
}
