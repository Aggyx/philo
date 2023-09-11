/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:27:38 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/11 21:10:01 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/lib.h"

static      int	get_next_id(t_var *var)
{	
	int	res;

	res = 0;
	pthread_mutex_lock(&var->idwrap);
	res = var->id;
	var->id++;
	pthread_mutex_unlock(&var->idwrap);
	return (res);
}

void    cpyvar(t_var *var, t_philos *philo)
{
	int i;

	i = 0;
    philo->tinit = var->tinit;
    gettimeofday(&philo->ts, NULL);
    philo->id = get_next_id(var);
    philo->thinkflag = 0;
    philo->time_die = var->time_die;
    philo->time_eat = var->time_eat;
    philo->time_slp = var->time_slp;
    philo->hseaten = 0;
    philo->dead = 0;
}


long	long	elapsedtime(struct timeval *ts)
{
	struct timeval		te;
	long long			time;

	time = 0;
	if (gettimeofday(&te, NULL) == 0)
	{
		time = ((te.tv_sec) * 1000 + (te.tv_usec) / 1000)
			- ((ts->tv_sec * 1000) + (ts->tv_usec / 1000));
		return (time);
	}
	else
		return (0);
}
