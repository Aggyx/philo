/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:06:46 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/15 16:56:11 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/lib.h"

static  void    destroy_mutexes(t_var *var)
{
	int	i;

	i = -1;
    pthread_mutex_destroy(&var->endwrap);
	while (++i < var->nb)
	{
        pthread_mutex_destroy(&var->forks[i]);
    	pthread_mutex_destroy(&var->philos[i].deadwrap);
        pthread_mutex_destroy(&var->philos[i].tmutex);
	}
}

static  void freealloc(t_var *var)
{
    if (var->proc != NULL)
        free(var->proc);
    if (var->philos != NULL)
        free(var->philos);
    if (var->forks != NULL)
        free(var->forks);
}

int ft_exit(t_var *var, int freeallocs, int freemutex, char *str)
{
    if (freeallocs)
    {
        freealloc(var);
        if (freemutex)
            destroy_mutexes(var);
    }
    if (str)
        printf("%s", str);
    return (1);
}
