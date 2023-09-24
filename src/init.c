/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:37:22 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/24 22:59:28 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/lib.h"

static void	philoinitvar(t_philos *philo, t_var *var, int id)
{
	philo->id = id + 1;
	philo->tinit = var->tinit;
	philo->thinkflag = 0;
	if (var->menu != -1 && var->menu)
		philo->haseat = var->menu;
	else
		philo->haseat = -1;
	philo->time_die = var->time_die;
	philo->time_slp = var->time_slp;
	philo->time_eat = var->time_eat;
	philo->dead = &var->end;
	philo->loneliness = 0;
}

void	philoconstructor(t_var *var)
{
	int	i;

	i = -1;
	if (var->nb == 1)
	{
		var->philos[0].lefork = &var->forks[0];
		philoinitvar(&var->philos[0], var, 0);
		var->philos[0].loneliness = 1;
	}
	else
	{
		while (++i < var->nb)
		{
			philoinitvar(&var->philos[i], var, i);
			var->philos[i].lefork = &var->forks[i];
			var->philos[i].rifork = &var->forks[(i + 1) % var->nb];
		}
	}
}

int	alloc(t_var *var)
{
	var->philos = (t_philos *)malloc(sizeof(t_philos) * var->nb);
	if (var->philos == NULL)
		return (ft_exit(var, 1, 0, "[ERROR]: Philo struct malloc failed."));
	var->proc = (pthread_t *)malloc(sizeof(pthread_t) * var->nb);
	if (var->proc == NULL)
		return (ft_exit(var, 1, 0, "[ERROR]: Process malloc failed."));
	var->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * var->nb);
	if (var->forks == NULL)
		return (ft_exit(var, 1, 0, "[ERROR]: mutex malloc failed."));
	return (0);
}

void	init_mutexes(t_var *var)
{
	int	i;

	i = -1;
	pthread_mutex_init(&var->endwrap, NULL);
	while (++i < var->nb)
	{
		pthread_mutex_init(&var->philos[i].tmutex, NULL);
		pthread_mutex_init(&var->forks[i], NULL);
	}
}
