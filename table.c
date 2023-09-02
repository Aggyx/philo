/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:07:32 by smagniny          #+#    #+#             */
/*   Updated: 2023/08/30 16:43:29 by smagniny         ###   ########.fr       */
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
	// if (i == 1 && id == i + 1)
	// 	return (NULL);
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

unsigned	long	elapsedtime(struct timeval *ts)
{
	struct timeval		te;

	if (gettimeofday(&te, NULL) == 0)
		return (((te.tv_usec) - (ts->tv_usec)) / 1000);
	else
		return (0);
}
