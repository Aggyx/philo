/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:37:36 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/04 17:59:20 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	diestarvation(t_var *shrd, t_localvar *lvar, int id)
{
	struct timeval		te;
	long long			time;

	if (gettimeofday(&te, NULL) == 0)
	{
		time = ((te.tv_sec) * 1000 + (te.tv_usec) / 1000)
			- ((lvar->me->ts.tv_sec) * 1000 + (lvar->me->ts.tv_usec) / 1000);
		if (time >= shrd->timedie)
		{
			printf("%lld %d died\n", elapsedtime(&shrd->tinit), id);
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
			pthread_mutex_lock(&phil->deathwrap);
			phil->deathflag = 1;
			pthread_mutex_unlock(&phil->deathwrap);
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
			pthread_mutex_lock(&phil->deathwrap);
			if (phil->deathflag)
			{
				pthread_mutex_unlock(&phil->deathwrap);
				turnoff = 1;
				break ;
			}
			else
				pthread_mutex_unlock(&phil->deathwrap);
			phil = phil->next;
		}
		if (phil == NULL)
			phil = varp->table->top;
	}
	setdeath(varp, turnoff);
	return (turnoff);
}

int	checklife(t_localvar *lvar)
{
	pthread_mutex_lock(&lvar->me->deathwrap);
	if (lvar->me->deathflag == 1)
	{
		pthread_mutex_unlock(&lvar->me->deathwrap);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&lvar->me->deathwrap);
		return (0);
	}
}
