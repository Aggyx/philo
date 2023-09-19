/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:01:29 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/19 18:46:38 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/lib.h"

static int	takeforks(t_philos *philo)
{
	if (seedeadval(philo) || theyhaveeat(philo))
		return (1);
	pthread_mutex_lock(philo->rifork);
	pthread_mutex_lock(philo->lefork);
	ft_printf(philo, "has taken a fork\n");
	ft_printf(philo, "has taken a fork\n");
	philo->lfk = 1;
	philo->rfk = 1;
	return (0);
}

static int	eat(t_philos *philo)
{
	if (seedeadval(philo) || theyhaveeat(philo))
		return (1);
	ft_printf(philo, EAT);
	if (ft_sleep(philo, philo->time_eat))
		return (1);
	ft_printf(philo, SLEEP);
	philo->lfk = 0;
	philo->rfk = 0;
	pthread_mutex_lock(&philo->deadwrap);
	gettimeofday(&philo->ts, NULL);
	pthread_mutex_unlock(&philo->deadwrap);
	pthread_mutex_unlock(philo->rifork);
	pthread_mutex_unlock(philo->lefork);
	pthread_mutex_lock(&philo->deadwrap);
	philo->haseat -= 1;
	pthread_mutex_unlock(&philo->deadwrap);
	philo->thinkflag = 1;
	if (ft_sleep(philo, philo->time_slp))
		return (1);
	return (0);
}

void	*routine(void *philp)
{
	t_philos	*philo;

	philo = (t_philos *)philp;
	if (gettimeofday(&philo->ts, NULL))
		return ((void *)1);
	if (philo->id % 2 == 0)
		usleep(philo->time_eat / 2);
	if (philo->loneliness)
		return ((void *)alone(philo));
	while (42)
	{
		if (takeforks(philo))
			break ;
		if (eat(philo))
			break ;
		if (diestarvation(philo))
			break ;
	}
	if (philo->rifork)
		pthread_mutex_unlock(philo->rifork);
	if (philo->lefork)
		pthread_mutex_unlock(philo->lefork);
	return ((void *)0);
}
