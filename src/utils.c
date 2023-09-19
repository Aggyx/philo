/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:27:38 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/19 09:34:18 by smagniny         ###   ########.fr       */
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

long	long	unsigned	timenow(struct timeval *te)
{
	long long unsigned	time;

	gettimeofday(te, NULL);
	time = (long long unsigned)((te->tv_sec * 1000) + (te->tv_usec / 1000));
	return (time);
}

void	ft_printf(t_philos *philo, char *action)
{
	if (strcmp(action, DIE) == 0)
		printf("%llu %d %s", elapsedtime(&philo->tinit), philo->id, action);
	else
	{
		pthread_mutex_lock(&philo->deadwrap);
		if (philo->dead == 0)
			printf("%llu %d %s", elapsedtime(&philo->tinit), philo->id, action);
		pthread_mutex_unlock(&philo->deadwrap);
	}
}

int		ft_sleep(t_philos *philo, int time)
{
	if (seedeadval(philo) == 0)
	{	
		usleep(time * 1000);
		return (0);
	}
	else
		return (1);
}
// void	ft_sleep(int time)
// {
// 	struct	timeval		te;
// 	long long unsigned	old_time;

// 	gettimeofday(&te, NULL);
// 	old_time = (long long unsigned)((te.tv_sec * 1000) + (te.tv_usec / 1000));
// 	while ((timenow() - old_time) < time)
// 		usleep();
// }
