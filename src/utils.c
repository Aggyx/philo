/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:27:38 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/25 21:41:37 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/lib.h"

void	*alone(t_philos *philo)
{
	pthread_mutex_lock(philo->lefork);
	printf("%lld %d has taken a fork\n", elapsedtime(&philo->tinit), philo->id);
	pthread_mutex_unlock(philo->lefork);
	while (42)
	{
		if (diestarvation(philo))
			break ;
	}
	return ((void *)0);
}

long	long	elapsedtime(struct timeval *ts)
{
	struct timeval		te;
	long long			time;

	time = 0;
	if (gettimeofday(&te, NULL) == 0)
	{
		time = ((te.tv_sec * 1000) + (te.tv_usec / 1000))
			- ((ts->tv_sec * 1000) + (ts->tv_usec / 1000));
		if (((ts->tv_sec * 1000) + (ts->tv_usec / 1000)) == 0)
			return (0);
		return (time);
	}
	else
		return (0);
}

long	long	timenow(struct timeval *te)
{
	long long	time;

	gettimeofday(te, NULL);
	time = (long long)((te->tv_sec * 1000) + (te->tv_usec / 1000));
	return (time);
}

void	ft_printf(t_philos *philo, char *action)
{
	pthread_mutex_lock(philo->diemutex);
	if (*philo->dead == 0)
	{
		pthread_mutex_unlock(philo->diemutex);
		printf("%llu %d %s", elapsedtime(&philo->tinit), philo->id, action);
	}
	else
	{
		pthread_mutex_unlock(philo->diemutex);
		if (ft_strcmp(action, DIE) == 0)
			printf("%llu %d %s", elapsedtime(&philo->tinit), philo->id, action);
	}
}

int	ft_sleep(int time)
{
	struct timeval		te;
	long long			start_time;

	start_time = timenow(&te);
	while (timenow(&te) < start_time + time)
		usleep(60);
	return (0);
}
