/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:01:29 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/11 21:57:36 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/lib.h"

// static int	takeforks(t_philos *philo, int nb)
// {
// 	if (pthread_mutex_lock(&philo->lefork) || nb == 1)
// 		return (1);
// 	printf("%lld %d has taken a fork\n", elapsedtime(&philo->tinit), philo->id);
// 	if (pthread_mutex_lock(&philo->rifork))
// 		return (1);
// 	printf("%lld %d has taken a fork\n", elapsedtime(&philo->tinit), philo->id);
// 	philo->lfk = 1;
// 	philo->rfk = 1;
// 	return (0);
// }

// static int	eat(t_philos *philo)
// {
// 	printf("%lld %d is eating\n", elapsedtime(&philo->tinit), philo->id);
// 	usleep(philo->time_eat * 1000);
// 	philo->lfk = 0;
// 	philo->rfk = 0;
// 	if (pthread_mutex_unlock(&philo->lefork))
// 		return (1);
// 	if (pthread_mutex_unlock(&philo->rifork))
// 		return (1);
// 	philo->hseaten += 1;
// 	philo->thinkflag = 1;
// 	if (gettimeofday(&philo->ts, NULL))
// 		return (1);
// 	printf("%lld %d is sleeping\n", elapsedtime(&philo->tinit), philo->id);
// 	return (0);
// }

void	*routine(void *varp)
{
	t_philos	philo;
	t_var		*var;

	var = (t_var *)varp;
	cpyvar(var, &philo);
	// while (var->end != 1 && philo.dead != 1)
	// {
	// 	if (takeforks(&philo, var->nb))
	// 	{
	// 		diestarvation(&philo);
	// 		continue ;
	// 	}
	// 	eat(&philo);
	// 	usleep(philo.time_slp);
	// }
	return ((void *)0);
}
