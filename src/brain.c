/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:01:29 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/24 23:23:15 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/lib.h"

static int	takeforks(t_philos *philo)
{
	if (*philo->dead || theyhaveeat(philo))
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
	ft_printf(philo, EAT);
	if (ft_sleep(philo, philo->time_eat))
		return (1);
	ft_printf(philo, SLEEP);
	philo->lfk = 0;
	philo->rfk = 0;
	gettimeofday(&philo->ts, NULL);
//he quitado el mutex de philo->ts
	pthread_mutex_unlock(philo->rifork);
	pthread_mutex_unlock(philo->lefork);
	pthread_mutex_lock(&philo->tmutex);
	philo->haseat -= 1;
	pthread_mutex_unlock(&philo->tmutex);
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
		usleep(50);
	if (philo->loneliness)
		return ((void *)alone(philo));
	while (42)
	{
		if (takeforks(philo))
			break ;
		if (eat(philo))
		{
			pthread_mutex_unlock(philo->rifork);
			pthread_mutex_unlock(philo->lefork);
			break ;
		}
		if (diestarvation(philo))
			break ;
	}
	return ((void *)0);
}
