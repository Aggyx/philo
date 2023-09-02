/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:37:36 by smagniny          #+#    #+#             */
/*   Updated: 2023/08/30 16:44:01 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	diestarvation(t_var *shrd, int id)
{
	struct timeval		te;
	unsigned	long	debug;

	debug = shrd->ts.tv_usec;
	if (gettimeofday(&te, NULL) == 0)
	{
		debug = (unsigned long)(te.tv_usec - shrd->ts.tv_usec);
		if (debug >= (shrd->timedie * 1000))
		{
			printf("[%lums] [%d] died\n", elapsedtime(&shrd->tinit), id);
			return (1);
		}
	}
	return (0);
}

int	killphilos(t_var *varcpy)
{

	while (varcpy->nbphilo--)
	{	
		if (pthread_join(varcpy->proc[varcpy->nbphilo], NULL))
			return (1);
	}
	if (cleantable(varcpy))
		exit(0);
	exit(0);
	return (0);
}
