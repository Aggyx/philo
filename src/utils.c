/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:27:38 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/14 05:39:34 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/lib.h"

long	long	elapsedtime(struct timeval *ts)
{
	struct timeval		te;
	long long			time;

	time = 0;
	if (gettimeofday(&te, NULL) == 0)
	{
		time = ((te.tv_sec * 1000) + (te.tv_usec / 1000))
			- ((ts->tv_sec * 1000) + (ts->tv_usec / 1000));
		return (time);
	}
	else
		return (0);
}

void	timenow(struct timeval *te)
{
	long long unsigned	time;

	gettimeofday(te, NULL);
	time = (long long unsigned)((te->tv_sec * 1000) + (te->tv_usec / 1000));
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
