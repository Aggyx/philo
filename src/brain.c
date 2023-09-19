/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:01:29 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/19 09:45:15 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/lib.h"

static int	takeforks(t_philos *philo)
{
	// printf("\n\n[INFO]: Philo %d is in routine with left (his) fork: %p \n", philo->id, philo->lefork);
	// printf("[INFO]: Philo %d is in routine with right (neigh) fork:			%p\n", philo->id, philo->rifork);
	if (seedeadval(philo) == 1)
		return (1);
	if (pthread_mutex_lock(philo->rifork))
	{
		printf("ID: %d  - Error at taking left fork\n", philo->id);
		return (1);
	}
	if (pthread_mutex_lock(philo->lefork))
	{
		pthread_mutex_unlock(philo->rifork);
		printf("ID: %d - Error at taking right fork\n", philo->id);
		return (1);
	}
	ft_printf(philo, "has taken neighbor fork\n");
	ft_printf(philo, "has taken his fork\n");
	philo->lfk = 1;
	philo->rfk = 1;
	return (0);
}

static int	eat(t_philos *philo)
{
	ft_printf(philo, EAT);
	if (ft_sleep(philo, philo->time_eat))
		return (1);
	philo->lfk = 0;
	philo->rfk = 0;
	philo->haseat -= 1;
	if (pthread_mutex_unlock(philo->rifork) || pthread_mutex_unlock(philo->lefork))
	{
		printf("error at unlocking\n");
		return (1);
	}
	pthread_mutex_lock(&philo->deadwrap);
	if (gettimeofday(&philo->ts, NULL))
		return (1);
	pthread_mutex_unlock(&philo->deadwrap);
	philo->thinkflag = 1;
	ft_printf(philo, SLEEP);
	return (0);
}

void	*routine(void *philp)
{
	t_philos	*philo;

	philo = (t_philos *)philp;
	pthread_mutex_lock(&philo->deadwrap);
	if (gettimeofday(&philo->ts, NULL))
		return ((void *)1);
	pthread_mutex_unlock(&philo->deadwrap);
	// if (philo->id % 2 == 1)
	// 	usleep(5);
	if (philo->loneliness)
		return ((void *)alone(philo));
	while (42)
	{
		if (takeforks(philo))
		{
			if (diestarvation(philo))
				break ;
			continue ;
		}
		if (eat(philo))
			break ;
		if (ft_sleep(philo, philo->time_slp))
			break;
		if (diestarvation(philo))
			break ;
	}
	return ((void *)0);
}
