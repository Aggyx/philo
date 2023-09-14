/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:53:53 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/14 05:17:14 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/lib.h"

/**
 * The function initializes variables and data structures, and returns 0 if successful.
 * 
 * @param var A pointer to a structure of type t_var.
 * @param argc The `argc` parameter is the number of command-line arguments passed to the program.
 * @param argv A pointer to an array of strings, where each string represents a command-line argument
 * passed to the program.
 * 
 * @return an integer value. If the function is successful, it returns 0. If there is an error, it
 * returns 1.
 */
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

/**
 * The main function initializes a variable, creates multiple threads, waits for them to finish, and
 * then exits.
 * 
 * @param argc The parameter `argc` is the number of command-line arguments passed to the program. It
 * includes the name of the program itself as the first argument.
 * @param argv The `argv` parameter is an array of strings that represents the command-line arguments
 * passed to the program. Each element of the array is a null-terminated string. The first element
 * (`argv[0]`) is usually the name of the program itself. The remaining elements (`argv[1]`
 * 
 * @return The main function is returning an integer value. In this case, it is returning 0.
 */

int	main(int argc, char **argv)
{
	t_var	var;
	int		i;

	i = -1;
	if (initialize(&var, argc, argv))
		return (1);
	while (++i < var.nb)
		pthread_create(&var.proc[i], NULL, routine, &var.philos[i]);
	i = -1;
	checkdeath(&var);
	while (++i < var.nb)
		pthread_join(var.proc[i], NULL);
	ft_exit(&var, 1, 1, "Finish\n");
	return (0);
}
