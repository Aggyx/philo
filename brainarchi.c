/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brainarchi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 18:13:00 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/04 18:29:48 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static	int	eatsleeprepeat(t_var *varcpy, t_localvar *localvar, int id, t_philo *neighb)
{
	//setting mutexwrap to occupied (1)
	if (binarymutexlock(localvar->me, neighb, varcpy, id))
	{
		if (diestarvation(varcpy, localvar, id))
			return (1);
		else
			return (checklife(localvar));
	}
	if (eat(localvar->me, neighb, varcpy, id) || checklife(localvar))
		return (1);
	printf("%lld %d is eating\n", elapsedtime(&varcpy->tinit), id);
	usleep(varcpy->time_eat * 1000);
	if (checklife(localvar) || finisheat(localvar->me, neighb, id, &varcpy->tinit))
		return (1);
	gettimeofday(&localvar->me->ts, NULL);
	usleep(varcpy->time_slp * 1000);
	localvar->me->thinkflag = 1;
	return (0);
}	

static	int	loopcheck(t_var *varcpy, t_localvar *localvar, int id)
{
	if (diestarvation(varcpy, localvar, id))
		return (1);
	if (localvar->me->thinkflag == 1)
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
	if (getstatusphilo(lvar->neighbor) || checklife(lvar))
	{
		if (getstatusphilo(lvar->neighbol) || checklife(lvar))
		{
			if (loopcheck(varcpy, lvar, id) || checklife(lvar))
				return (1);
		}
		else if (getstatusphilo(lvar->me) || checklife(lvar))
		{
			if (loopcheck(varcpy, lvar, id) || checklife(lvar))
				return (1);
		}
		else
		{
			if (eatsleeprepeat(varcpy, lvar, id, lvar->neighbol) || checklife(lvar))
				return (1);
		}
	}
	else if (getstatusphilo(lvar->me) || checklife(lvar))
	{
		if (loopcheck(varcpy, lvar, id) || checklife(lvar))
			return (1);
	}
	else
	{
		if (eatsleeprepeat(varcpy, lvar, id, lvar->neighbor) || checklife(lvar))
			return (1);
	}
	return (0);
}
