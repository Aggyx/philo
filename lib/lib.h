/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:41:11 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/14 05:37:28 by smagniny         ###   ########.fr       */
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
	struct timeval	ts2;
	struct timeval	ts;
	struct timeval	tinit;
	int				id;
	int				thinkflag;
	int				time_die;
	int				time_eat;
	int				time_slp;
	int				dead;
	int				iter;
	pthread_mutex_t	*lefork;
	int				lfk;
	pthread_mutex_t	*rifork;
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
	pthread_mutex_t	endwrap;
	int				end;
	struct timeval	tinit; // initializar tINITT
	pthread_mutex_t	*forks; //alloc && initmutex
	int				id;
}	t_var;

//initializing
	//parse input and enter values to main struct.
int				getargs(int argc, char **argv, t_var *var);
int				alloc(t_var *var);
void			init_mutexes(t_var *var);
//routina
void			*routine(void *varp);
int				diestarvation(t_philos *philo);
//Utils
void			timenow(struct timeval *te);
long	long	elapsedtime(struct timeval *ts);
void			philoconstructor(t_var *var);
void			ft_sleep(int time);
//Gestión de errores
void			checkdeath(t_var *var);
int 			ft_exit(t_var *var, int freeallocs, int freemutex, char *str);
#endif