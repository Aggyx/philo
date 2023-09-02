/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philobrain.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 12:35:56 by smagniny          #+#    #+#             */
/*   Updated: 2023/08/30 15:54:15 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	getstatusphilo(t_philo	*philo)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&philo->mfkwrap);
	res = philo->fkwrap;
	pthread_mutex_unlock(&philo->mfkwrap);
	return (res);
}

int	binarymutexlock(t_philo *me, t_philo *neighbor)
{	
	if (me->id == neighbor->id)
		return (1);
	if (pthread_mutex_lock(&me->mfkwrap))
		return (1);
	me->fkwrap = 1;
	if (pthread_mutex_unlock(&me->mfkwrap))
		return (1);
	if (pthread_mutex_lock(&neighbor->mfkwrap))
		return (1);
	neighbor->fkwrap = 1;
	if (pthread_mutex_unlock(&neighbor->mfkwrap))
		return (1);
	return (0);
}

int	binarymutexunlock(t_philo *me, t_philo *neighbor)
{
	if (me->id == neighbor->id)
		return (1);
	if (pthread_mutex_lock(&me->mfkwrap))
		return (1);
	me->fkwrap = 0;
	if (pthread_mutex_unlock(&me->mfkwrap))
		return (1);
	if (pthread_mutex_lock(&neighbor->mfkwrap))
		return (1);
	neighbor->fkwrap = 0;
	if (pthread_mutex_unlock(&neighbor->mfkwrap))
		return (1);
	return (0);
}

int	eat(t_philo *me, t_philo *neighbor)
{
	if (pthread_mutex_lock(&neighbor->fork))
		return (1);
	if (pthread_mutex_lock(&me->fork))
		return (1);
	me->hseaten += 1;
	me->fk = 1;
	neighbor->fk = 1;
	me->is_eating = 1;
	return (0);
}

int	finisheat(t_philo *me, t_philo *neighbor, int id, struct timeval *ts)
{
	me->fk = 0;
	neighbor->fk = 0;
	if (pthread_mutex_unlock(&me->fork))
		return (1);
	if (pthread_mutex_unlock(&neighbor->fork))
		return (1);
	binarymutexunlock(me, neighbor);
	me->is_eating = 0;
	printf("[%lums] [%d] is sleeping\n", elapsedtime(ts), id);
	return (0);
}
