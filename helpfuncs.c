/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpfuncs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:39:44 by smagniny          #+#    #+#             */
/*   Updated: 2023/08/27 11:22:18 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	lstsize(t_table *table)
{
	size_t	i;
	t_philo	*ptr;

	if (table->top == NULL)
		return (0);
	i = 0;
	ptr = table->top;
	if (ptr)
		i += 1;
	while (ptr && ptr->next != NULL)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}

int	push(t_table *table, int id)
{
	t_philo	*current;
	t_philo	*newphilo;

	newphilo = (t_philo *)malloc(sizeof(t_philo) * 1);
	if (table == NULL || newphilo == NULL)
		return (1);
	newphilo->id = id;
	newphilo->hseaten = 0;
	if (pthread_mutex_init(&newphilo->mfkwrap, NULL))
		return (1);
	if (pthread_mutex_init(&newphilo->fork, NULL))
		return (1);
	newphilo->fkwrap = 0;
	newphilo->fk = 0;
	current = table->top;
	// mesa vacia
	if (current == NULL)
	{
		table->top = newphilo;
		newphilo->prev = NULL;
		newphilo->next = NULL;
	}
	else
	{
		while (current->next != NULL)
			current = current->next;
		// anadiendo elem al final de la mesa
		current->next = newphilo;
		newphilo->prev = current;
		newphilo->next = NULL;
	}
	return (0);
}

t_philo	*lastelem(t_table	*stack)
{
	t_philo	*tmp;

	tmp = stack->top;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}