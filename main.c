/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:53:53 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/11 21:41:43 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/lib.h"

static int	initialize(t_var *var, int argc, char **argv)
{
	if (getargs(argc, argv, var))
		return (1);
	if (alloc(var))
		return (1);
	init_mutexes(var);
	if (gettimeofday(&var->tinit, NULL))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_var	var;
	int		i;

	i = -1;
	if (initialize(&var, argc, argv))
		return (1);
	while (++i < var.nb)
		pthread_create(&var.proc[i], NULL, routine, (void *)&var);
	i = 0;
	while (++i < var.nb)
		pthread_join(var.proc[i], NULL);
	ft_exit(&var, 1, 1, NULL);
	return (0);
}
