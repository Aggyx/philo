/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:06:48 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/11 21:26:15 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/lib.h"

void	diestarvation(t_philos *philo)
{
	if (elapsedtime(&philo->ts) >= (long long)philo->time_die)
	{
		philo->dead = 1;
		printf("%llu %d has died\n", elapsedtime(&philo->tinit), philo->id);
	}
	if (philo->thinkflag)
		printf("%llu %d is thinking\n", elapsedtime(&philo->tinit), philo->id);
}
