/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:06:48 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/14 05:28:22 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/lib.h"

static void	killeveryone(t_var *var)
{
	int	i;

	i = -1;
	while (++i < var->nb)
		var->philos[i].dead = 1;
}

void	checkdeath(t_var *var)
{
	int	i;

	while (42)
	{
		i = -1;
		while (++i < var->nb)
		{
			if (var->philos[i].dead)
			{
				killeveryone(var);
				break ;
			}
			if (i == var->nb - 1)
				i = -1;
		}
		break ;
	}
}

int	diestarvation(t_philos *philo)
{
	if (elapsedtime(&philo->ts) >= (long long)philo->time_die)
	{
		philo->dead = 1;
		printf("%llu %d has died\n", elapsedtime(&philo->tinit), philo->id);
		return (1);
	}
	if (philo->thinkflag)
		printf("%llu %d is thinking\n", elapsedtime(&philo->tinit), philo->id);
	return (0);
}
