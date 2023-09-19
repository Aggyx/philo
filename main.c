/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:53:53 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/19 18:33:50 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/lib.h"

/*
1 800 200 200
a philo should die
4 310 200 100
a philo should die
4 200 205 200
a philo should die
5 800 200 200 7
no one should die, simulation should stop after 7 eats
4 410 200 200 10
no one should die, simulation should stop after 10 eats
-5 600 200 200
should error and not run (no crashing)
4 -5 200 200
should error and not run (no crashing)
4 600 -5 200
should error and not run (no crashing)
4 600 200 -5
should error and not run (no crashing)
4 600 200 200 -5
should error and not run (no crashing)

5 800 200 200
no one should die
5 600 150 150
no one should die
4 410 200 200
no one should die
100 800 200 200
no one should die
105 800 200 200
no one should die
200 800 200 200
no one should die

Black \033[0;30m
Red \033[0;31m
Green \033[0;32m
Yellow \033[0;33m
Blue \033[0;34m
Purple \033[0;35m
Cyan \033[0;36m
White \033[0;37m
*/

//parse utils 91

static int	initialize(t_var *var, int argc, char **argv)
{
	if (getargs(argc, argv, var))
		return (1);
	if (alloc(var))
		return (1);
	init_mutexes(var);
	if (gettimeofday(&var->tinit, NULL))
		return (1);
	philoconstructor(var);
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
		pthread_create(&var.proc[i], NULL, routine, (void *)&var.philos[i]);
	i = -1;
	checkdeath(&var);
	while (++i < var.nb)
		pthread_join(var.proc[i], NULL);
	ft_exit(&var, 1, 1, NULL);
	return (0);
}
