/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:37:00 by smagniny          #+#    #+#             */
/*   Updated: 2023/08/30 15:40:20 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	boxisnumberandreturn(char *argv)
{
	int	i;
	int	r;
	r = 0;
	i = 0;
	if (!argv[i])
		exit(1);
	while (argv[i] == ' ' || argv[i] == '\t' || argv[i] == '\n' \
		|| argv[i] == '\v' || argv[i] == '\f' || argv[i] == '\r')
		i++;
	while (argv[i] && argv[++i] != '\0')
	{
		if (argv[i] < '0' || argv[i] > '9')
		{
			printf("[ERROR]: Invalid Arguments.\n");
			exit(1);
		}
	}
	r = atoi(argv);
	if (r == -77)
		return (0);
	return (r);
}

int	getargs(int argc, char **argv, t_var *var)
{
	if (argc != 5 && argc != 6)
	{
		printf("Wrong arguments..\n");
		return (0);
	}
	var->nbphilo = boxisnumberandreturn(argv[1]);
	var->timedie = boxisnumberandreturn(argv[2]);
	var->time_eat = boxisnumberandreturn(argv[3]);
	var->time_slp = boxisnumberandreturn(argv[4]);
	if (argc == 6)
		var->menu = boxisnumberandreturn(argv[5]);
	else
		var->menu = -77;
	var->id = 1;
	var->table = (t_table *)malloc(sizeof(t_table) * 1);
	var->proc = (pthread_t *)malloc(sizeof(pthread_t *) * var->nbphilo);
	if (var->proc == NULL || var->table == NULL)
	{
		printf("[ERROR]:Allocation failed.\n");
		return (0);
	}
	var->table->top = NULL;
	return (argc);
}

int	setlocalvar(t_localvar *localvar, t_var	*varcpy, int id)
{
	localvar->thinkflag = 0;
	if (gettimeofday(&varcpy->ts, NULL))
		return (1);
	if (gettimeofday(&varcpy->tinit, NULL))
		return (1);
	localvar->neighbor = getphilo(varcpy->table, id + 1);
	if (!localvar->neighbor || localvar->neighbor == NULL)
		return (1);
	localvar->neighbol = getphilo(varcpy->table, id - 1);
	if (!localvar->neighbol || localvar->neighbol == NULL)
		return (1);
	localvar->me = getphilo(varcpy->table, id);
	if (!localvar->me || localvar->me == NULL)
		return (1);
	return (0);
}
