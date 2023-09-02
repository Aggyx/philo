/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brainarchi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 18:13:00 by smagniny          #+#    #+#             */
/*   Updated: 2023/08/30 16:18:15 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static	int	eatsleeprepeat(t_var *varcpy, t_localvar *localvar, int id, t_philo *neighb)
{
	//setting mutexwrap to occupied (1)
	if (binarymutexlock(localvar->me, neighb))
	{
		if (diestarvation(varcpy, id))
			return (1);
		else
			return (0);
	}
	if (eat(localvar->me, neighb))
		return (1);
	usleep(varcpy->time_eat * 1000);
	printf("[%lums] [%d] is eating\n", elapsedtime(&varcpy->tinit), id);
	if (finisheat(localvar->me, neighb, id, &varcpy->tinit))
		return (1);
	gettimeofday(&varcpy->ts, NULL);
	usleep(varcpy->time_slp * 1000);
	localvar->thinkflag = 0;
	return (0);
}	

static	int	loopcheck(t_var *varcpy, t_localvar *localvar, int id)
{
	if (diestarvation(varcpy, id))
		return (1);
	if (!localvar->thinkflag)
	{	
		printf("[%lums] [%d] is thinking\n", elapsedtime(&varcpy->tinit), id);
		localvar->thinkflag = 1;
	}
	else
		usleep(10);
	return (0);
}

int	brain(t_var *varcpy, t_localvar *lvar, int id)
{
	if (getstatusphilo(lvar->neighbor))
	{
		// if (getstatusphilo(lvar->neighbol))
		// {
		// 	if (loopcheck(varcpy, lvar, id))
		// 		return (1);
		// }
		// else if (getstatusphilo(lvar->me))
		// {
		// 	if (loopcheck(varcpy, lvar, id))
		// 		return (1);
		// }
		// else
		// {
		// 	if (eatsleeprepeat(varcpy, lvar, id, lvar->neighbol, 0))
		// 		return (1);
		// }
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
		if (eatsleeprepeat(varcpy, lvar, id, lvar->neighbor))
			return (1);
	}
	return (0);
}
