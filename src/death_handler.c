/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:06:48 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/24 23:36:40 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/lib.h"

static	int	timesincelasteat(t_philos *philo, t_var  *var)
{
	long long int	num;

	num = 0;
	pthread_mutex_lock(&philo->tmutex);
	num = elapsedtime(&philo->ts);
	pthread_mutex_unlock(&philo->tmutex);
	if (num >= var->time_die)
	{
		pthread_mutex_lock(&var->endwrap);
		var->end = 1;
		pthread_mutex_unlock(&var->endwrap);
		return (1);
	}
	return (0);
}

static int	check_eatandeath(t_var *var, t_philos *philo, int sum)
{
	if (seedeadval(var))
		return (1);
	if (sum == var->nb)
		return (1);
	if (timesincelasteat(philo, var))
		return (1);
	return (0);
}

void	checkdeath(t_var *var)
{
	int	i;
	int	sum;

	sum = 0;
	while (42)
	{
		i = -1;
		while (++i < var->nb)
		{
			if (theyhaveeat(&var->philos[i]))
				sum++;
			if (check_eatandeath(var, &var->philos[i], sum))
			{
				var->end = 1;
				ft_printf(&var->philos[i], DIE);
				break ;
			}
			if (i == var->nb - 1)
			{	
				i = -1;
				sum = 0;
			}
		}
		break ;
	}
}

int	diestarvation(t_philos *philo)
{
	if (*philo->dead)
		return (1);
	if (philo->thinkflag)
	{
		ft_printf(philo, THINK);
		philo->thinkflag = 0;
	}
	return (0);
}
