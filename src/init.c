/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:37:22 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/14 05:23:35 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/lib.h"

static	void	philoinitvar(t_philos *philo, t_var *var , int id)
{
	philo->id = id + 1;
	philo->tinit = var->tinit;
	philo->thinkflag = 0;
	philo->time_die = var->time_die;
	philo->time_slp = var->time_slp;
	philo->time_eat = var->time_eat;
	philo->dead = 0;
	philo->iter = 0;
}

void	philoconstructor(t_var *var)
{
	int	i;

	i = -1;
	if (var->nb == 1)
	{
		var->philos[0].lefork = &var->forks[0];
		--var->nb;
	}
	while (++i < var->nb)
	{
		var->philos[i].lefork = &var->forks[i];
		var->philos[i].rifork = &var->forks[(i + 1) % var->nb];
	}
	i = -1;
	while (++i < var->nb)
		philoinitvar(&var->philos[i], var, i);
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
		pthread_mutex_init(&var->forks[i], NULL);
}

