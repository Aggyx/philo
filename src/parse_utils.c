/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:27:33 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/11 21:22:07 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/lib.h"

static	int	ft_atoi(const char *str)
{
	unsigned int		nb;
	int					sign;

	sign = 1;
	nb = 0;
	while (*str == ' ' || *str == '\t' || *str == '\f'
		|| *str == '\r' || *str == '\n' || *str == '\v')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = (nb * 10) + (*str - '0');
		str++;
	}
	if (nb >= 2147483647 && sign == 1)
		return (0);
	else if (nb >= 2147483648 && sign == -1)
		return (0);
	return ((sign * nb));
}

static int	parseparam(char *argv)
{
	int	i;
	int	r;

	r = 1;
	i = 0;
	if (!argv[i])
		return (1);
	while (argv[i] == ' ' || argv[i] == '\t' || argv[i] == '\n' \
		|| argv[i] == '\v' || argv[i] == '\f' || argv[i] == '\r')
		i++;
	while (argv[i] && argv[++i] != '\0')
	{
		if (argv[i] < '0' || argv[i] > '9')
		{
			printf("[ERROR]: Invalid Arguments.\n");
			r = 0;
		}
	}
	if (r)
		r = ft_atoi(argv);
	if (r <= 0)
		return (0);
	return (r);
}

int	getargs(int argc, char **argv, t_var *var)
{
	if (argc < 5 || argc > 6)
		return (ft_exit(var, 0, 0, "[ERROR]: Wrong number of arguments\n"));
	var->nb = parseparam(argv[1]);
	var->time_die = parseparam(argv[2]);
	var->time_eat = parseparam(argv[3]);
	var->time_slp = parseparam(argv[4]);
	if (argc == 6)
		var->menu = parseparam(argv[5]);
	else
		var->menu = -1;
	if (var->nb == 0 || var->time_die == 0 || var->time_eat == 0
		|| var->time_slp == 0 || var->menu == 0)
		return (ft_exit(var, 0, 0, "[ERROR]: Arguments has invalid character\n"));
	var->id = 1;
	var->end = 0;
	return (0);
}

