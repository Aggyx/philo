/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:06:48 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/19 18:46:11 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/lib.h"

static void	killeveryone(t_var *var)
{
	int	i;

	i = -1;
	while (++i < var->nb)
	{
		pthread_mutex_lock(&var->philos[i].deadwrap);
		var->philos[i].dead = 1;
		pthread_mutex_unlock(&var->philos[i].deadwrap);
	}
}

static	int	timesincelasteat(t_philos *philo, long long time_die)
{
	long long int	num;

	num = 0;
	pthread_mutex_lock(&philo->deadwrap);
	num = elapsedtime(&philo->ts);
	if (num >= time_die)
	{
		philo->dead = 1;
		pthread_mutex_unlock(&philo->deadwrap);
		return (1);
	}
	pthread_mutex_unlock(&philo->deadwrap);
	return (0);
}

static int	check_eatandeath(t_var *var, t_philos *philo)
{
	if (seedeadval(philo))
		return (1);
	if (timesincelasteat(philo, var->time_die))
	{
		ft_printf(philo, DIE);
		return (1);
	}
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
			if (check_eatandeath(var, &var->philos[i]) || sum == var->nb)
			{
				killeveryone(var);
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
	if (seedeadval(philo))
		return (1);
	if (philo->thinkflag)
	{
		ft_printf(philo, THINK);
		philo->thinkflag = 0;
	}
	return (0);
}
