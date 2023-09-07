/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brainarchi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 18:13:00 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/07 17:18:02 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static	int	eatsleeprepeat(t_var *varcpy, t_localvar *localvar, int id, t_philo *neighb)
{
	if (eat(localvar->me, neighb, varcpy, id))
		return (1);
	printf("%lld %d is eating\n", elapsedtime(&varcpy->tinit), id);
	usleep(varcpy->time_eat * 1000);
	if (finisheat(localvar->me, neighb, id, &varcpy->tinit))
		return (1);
	gettimeofday(&localvar->me->ts, NULL);
	usleep(varcpy->time_slp * 1000);
	localvar->me->thinkflag = 1;
	return (0);
}	

static	int	loopcheck(t_var *varcpy, t_localvar *localvar, int id)
{
	if (diestarvation(varcpy, localvar, id, 0))
		return (1);
	if (localvar->me->thinkflag)
	{
		printf("%lld %d is thinking\n", elapsedtime(&varcpy->tinit), id);
		localvar->me->thinkflag = 0;
	}
	else
		usleep(10);
	return (0);
}

int	brain(t_var *varcpy, t_localvar *lvar, int id)
{
	if (getstatusphilo(lvar->neighbor))
	{
		if (getstatusphilo(lvar->neighbol))
		{
			if (loopcheck(varcpy, lvar, id))
				return (1);
		}
		else if (getstatusphilo(lvar->me))
		{
			if (loopcheck(varcpy, lvar, id))
				return (1);
		}
		else
		{
			if (eatsleeprepeat(varcpy, lvar, id, lvar->neighbol))
				return (1);
		}
	}
	else if (lockneigh(lvar->neighbor, varcpy, id) || getstatusphilo(lvar->me))
	{
		if (loopcheck(varcpy, lvar, id))
			return (1);
	}
	else
	{
		if (lvar->neighbor != lvar->me)
			lockme(lvar->me, varcpy, id);
		else
			return (1);
		if (eatsleeprepeat(varcpy, lvar, id, lvar->neighbor))
			return (1);
	}
	return (0);
}
