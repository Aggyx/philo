/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:37:36 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/07 17:26:32 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	diestarvation(t_var *shrd, t_localvar *lvar, int id, int routineflag)
{
	struct timeval		te;
	long long			time;

	if (gettimeofday(&te, NULL) == 0)
	{
		time = ((te.tv_sec) * 1000 + (te.tv_usec) / 1000)
			- ((lvar->me->ts.tv_sec) * 1000 + (lvar->me->ts.tv_usec) / 1000);
		if (time >= shrd->timedie)
		{
			if (routineflag)
			{
				printf("%lld %d died\n", elapsedtime(&shrd->tinit), id);
				pthread_mutex_lock(&lvar->me->deadwrap);
				lvar->me->dead = 1;
				pthread_mutex_unlock(&lvar->me->deadwrap);
			}
			return (1);
		}
	}
	return (0);
}

static void	setdeath(t_var *varp, int turnoff)
{
	t_philo	*phil;

	phil = varp->table->top;
	if (turnoff)
	{
		while (phil != NULL)
		{
			pthread_mutex_lock(&phil->deadwrap);
			phil->dead = 1;
			pthread_mutex_unlock(&phil->deadwrap);
			phil = phil->next;
		}
	}
}

int	checkdeath(t_var *varp)
{
	t_philo	*phil;
	int		turnoff;

	turnoff = 0;
	phil = varp->table->top;
	while (42 && !turnoff)
	{
		while (phil != NULL)
		{
			// if (/*current_time - philo_start_time - philo_last_meal >= time_to_die */)
			pthread_mutex_lock(&phil->deadwrap);
			if (phil->dead)
			{
				pthread_mutex_unlock(&phil->deadwrap);
				turnoff = 1;
				setdeath(varp, turnoff);
				pthread_mutex_lock(&varp->endwrap);
				varp->end = 1;
				pthread_mutex_unlock(&varp->endwrap);
			}
			else
				pthread_mutex_unlock(&phil->deadwrap);
			phil = phil->next;
		}
		if (phil == NULL)
			phil = varp->table->top;
		usleep(100);
	}
	return (turnoff);
}
