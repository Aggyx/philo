/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:41:11 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/11 21:48:06 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

//variables locales de cada rutina 
//junto con variables mutex para coordinación de las variables forks.
typedef struct s_philo
{
	struct timeval	ts;
	struct timeval	tinit;
	int				id;
	int				thinkflag;
	int				time_die;
	int				time_eat;
	int				time_slp;
	int				hseaten;
	int				dead;
	pthread_mutex_t	lefork;
	int				lfk;
	pthread_mutex_t	rifork;
	int				rfk;
}	t_philos;

//variables de main y params pasados a cada proceso
typedef struct s_var
{
	pthread_t		*proc;// alloc
	t_philos		*philos;// alloc
	int				nb;
	int				time_die;
	int				time_eat;
	int				time_slp;				
	int				menu;
	int				end;
	struct timeval	tinit; // initializar tINITT
	pthread_mutex_t	*forks; //alloc && initmutex
	pthread_mutex_t	idwrap; //initvarmutex
	int				id;
}	t_var;

//initializing
	//parse input and enter values to main struct.
int				getargs(int argc, char **argv, t_var *var);
int				alloc(t_var *var);
void			init_mutexes(t_var *var);
//routina
void			*routine(void *varp);
void			diestarvation(t_philos *philo);
//Utils
long	long	elapsedtime(struct timeval *ts);
void			cpyvar(t_var *var, t_philos *philo);
//Gestión de errores
int 			ft_exit(t_var *var, int freeallocs, int freemutex, char *str);
#endif