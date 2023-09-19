/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:06:48 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/19 10:10:25 by smagniny         ###   ########.fr       */
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

// static	int	atetoolate(t_philos *philo, t_var *var)
// {
// 	pthread_mutex_lock(&philo->tmutex);
// 	if (elapsedtime(&philo->ts) >= (long long int)philo->time_die + 10)
// 	{
// 		pthread_mutex_unlock(&philo->tmutex);
// 		printf("Ate too late");
// 		pthread_mutex_lock(&philo->deadwrap);
// 		philo->dead = 1;
// 		pthread_mutex_unlock(&philo->deadwrap);
// 		return (1);
// 	}
// 	if (var->menu)
// 		seeifateenough(philo);
// 	pthread_mutex_unlock(&philo->tmutex);
// 	return (0);
// }

static	int	theyhaveeat(t_philos *philo)
{
	pthread_mutex_lock(&philo->deadwrap);
	if (philo->haseat == 0)
	{
		// printf("Philo %d ate enough", philo->id);
		pthread_mutex_unlock(&philo->deadwrap);
		return (1);
	}
	pthread_mutex_unlock(&philo->deadwrap);
	return (0);
}

static	int	timesincelasteat(t_philos *philo, long long time_die)
{
	long	long	int	num;

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

int	seedeadval(t_philos *philo)
{
	pthread_mutex_lock(&philo->deadwrap);
	if (philo->dead == 1)
	{
		pthread_mutex_unlock(&philo->deadwrap);
		return (1);
	}
	pthread_mutex_unlock(&philo->deadwrap);
	return (0);
}

void	checkdeath(t_var *var)
{
	int	i;
	int sum;

	sum = 0;
	while (42)
	{
		i = -1;
		while (++i < var->nb)
		{
			// if un philo se retrasa -> kill todos
			if (theyhaveeat(&var->philos[i]))
				sum++;
			if (sum == var->nb)
			{
				printf("All philos ate enough");
				break ;
			}
			if (seedeadval(&var->philos[i]))
			{
				// printf("[M] KILLING EVERYBODY\n");
				killeveryone(var);
				break ;
			}
			if (timesincelasteat(&var->philos[i], var->time_die))
			{
				killeveryone(var);
				printf("%llu %d has died\n", elapsedtime(&var->tinit), var->philos[i].id);
				break ;
				// printf("[M][%llu] PHILO %d did not ate on time\n", elapsedtime(&var->tinit), var->philos[i].id);
			}
			if (i == var->nb - 1)
				i = -1;
		}
		break ;
	}
}

int	diestarvation(t_philos *philo)
{
	if (seedeadval(philo))
	{
		ft_printf(philo, DIE);
		return (1);
	}
	if (philo->thinkflag)
	{
		ft_printf(philo, THINK);
		philo->thinkflag = 0;
	}
	if (philo->haseat == 0)
	{
		// printf("philo ate enough\n");
		return (1);
	}
	return (0);
}
