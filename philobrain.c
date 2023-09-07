/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philobrain.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 12:35:56 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/07 16:44:51 by smagniny         ###   ########.fr       */
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

int	lockme(t_philo *me, t_var *varp, int id)
{
	if (pthread_mutex_lock(&me->mfkwrap))
		return (1);
	printf("%lld %d has taken a fork\n", elapsedtime(&varp->tinit), id);
	me->fkwrap = 1;
	if (pthread_mutex_unlock(&me->mfkwrap))
		return (1);
	return (0);
}

int	lockneigh(t_philo *neighbor, t_var *varp, int id)
{
	if (pthread_mutex_lock(&neighbor->mfkwrap))
		return (1);
	printf("%lld %d has taken a fork\n", elapsedtime(&varp->tinit), id);
	neighbor->fkwrap = 1;
	if (pthread_mutex_unlock(&neighbor->mfkwrap))
		return (1);
	return (0);
}

int	binarymutexlock(t_philo *me, t_philo *neighbor, t_var *varp, int id)
{	
	if (pthread_mutex_lock(&me->mfkwrap))
		return (1);
	printf("%lld %d has taken a fork\n", elapsedtime(&varp->tinit), id);
	me->fkwrap = 1;
	if (pthread_mutex_unlock(&me->mfkwrap))
		return (1);
	if (me->id == neighbor->id)
		return (1);
	if (pthread_mutex_lock(&neighbor->mfkwrap))
		return (1);
	printf("%lld %d has taken a fork\n", elapsedtime(&varp->tinit), id);
	neighbor->fkwrap = 1;
	if (pthread_mutex_unlock(&neighbor->mfkwrap))
		return (1);
	return (0);
}

int	binarymutexunlock(t_philo *me, t_philo *neighbor)
{
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

int	eat(t_philo *me, t_philo *neighbor, t_var *varcpy, int id)
{
	if (pthread_mutex_lock(&neighbor->fork))
		return (1);
	if (pthread_mutex_lock(&me->fork))
		return (1);
	me->fk = 1;
	neighbor->fk = 1;
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
	me->hseaten += 1;
	printf("%lld %d is sleeping\n", elapsedtime(ts), id);
	return (0);
}
