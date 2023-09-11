/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:37:22 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/11 21:23:29 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/lib.h"

int	alloc(t_var *var)
{
	var->philos = (t_philos *)malloc(sizeof(t_philos *) * var->nb);
	if (var->philos == NULL)
		return (ft_exit(var, 1, 0, "[ERROR]: Philo struct malloc failed."));
	var->proc = (pthread_t *)malloc(sizeof(pthread_t *) * var->nb);
	if (var->proc == NULL)
		return (ft_exit(var, 1, 0,"[ERROR]: Process malloc failed."));
	var->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t *) * var->nb);
	if (var->forks == NULL)
		return (ft_exit(var, 1, 0,"[ERROR]: Fork mutexes struct malloc failed."));
	return (0);
}

void	init_mutexes(t_var *var)
{
	int	i;

	i = -1;
	pthread_mutex_init(&var->idwrap, NULL);
	while (++i < var->nb)
		pthread_mutex_init(&var->forks[i], NULL);
	i = 0;
	if (var->nb > 1)
	{
		var->philos[i].lefork = var->forks[var->nb - 1];
		var->philos[i].rifork = var->forks[0];
		while (++i < var->nb)
		{
			var->philos[i].lefork = var->forks[i - 1];
			var->philos[i].rifork = var->forks[i];
		}
	}
	else
		var->philos[0].lefork = var->forks[0];
}

