/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:07:32 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/04 15:36:22 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static	void	freestack(t_table *stack)
{
	t_philo	*node;
	t_philo	*temp;

	node = stack->top;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		free(temp);
	}
	free(stack);
}

int	maketable(t_var *var)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&var->idwrap, NULL))
		return (1);
	while (++i <= var->nbphilo)
	{
		if (push(var->table, i))
			return (1);
	}
	if (gettimeofday(&var->tinit, NULL))
		return (1);
	return (0);
}

int	cleantable(t_var *var)
{
	t_philo	*mirror;

	mirror = var->table->top;
	if (pthread_mutex_destroy(&var->idwrap))
		return (1);
	while (mirror != NULL)
	{
		if (pthread_mutex_destroy(&mirror->mfkwrap))
			return (1);
		if (pthread_mutex_destroy(&mirror->fork))
			return (1);
		mirror = mirror->next;
	}
	freestack(var->table);
	free(var->proc);
	return (0);
}

t_philo	*getphilo(t_table *table, int id)
{
	t_philo	*tmp;
	int		i;

	i = lstsize(table);
	if (id == 0)
		return (lastelem(table));
	else if (id == i + 1)
		return (table->top);
	else
	{	
		tmp = table->top;
		while (tmp != NULL)
		{
			if (tmp->id == id)
				return (tmp);
			else
				tmp = tmp->next;
		}
		return (NULL);
	}
}

long	long	elapsedtime(struct timeval *ts)
{
	struct timeval		te;
	long long			time;

	time = 0;
	if (gettimeofday(&te, NULL) == 0)
	{
		time = ((te.tv_sec) * 1000 + (te.tv_usec) / 1000)
			- ((ts->tv_sec * 1000) + (ts->tv_usec / 1000));
		return (time);
	}
	else
		return (0);
}
